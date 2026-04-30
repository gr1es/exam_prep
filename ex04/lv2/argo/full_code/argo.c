#include "argo.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int		parse_value(json *dst, FILE *stream);
void	free_json(json val);

// =============================================================================
// 1. UTILITIES
// =============================================================================

int	error_out(int c)
{
	if (c == EOF)
		printf("unexpected end of input\n");
	else
		printf("unexpected token '%c'\n", c);
	return (-1);
}

int	peek(FILE *stream)
{
	int	c;

	c = getc(stream);
	if (c != EOF)
		ungetc(c, stream);
	return (c);
}

// =============================================================================
// 2. LEAK PREVENTION
// =============================================================================

void	free_map(map *m)
{
	if (!m)
		return ;
	for (size_t i = 0; i < m->size; i++)
	{
		free(m->data[i].key);
		free_json(m->data[i].value);
	}
	free(m->data);
	free(m);
}

void	free_json(json val)
{
	if (val.type == STRING)
		free(val.string);
	if (val.type == MAP)
		free_map(val.map);
}

// =============================================================================
// 3. PARSERS
// =============================================================================

int	parse_string(char **dst, FILE *stream)
{
	int		len;
	int		c;
	char	*str;

	len = 0;
	if (getc(stream) != '"')
		return (-1);
	str = malloc(1);
	str[0] = '\0';
	while ((c = getc(stream)) != EOF)
	{
		if (c == '"')
		{
			*dst = str;
			return (1);
		}
		if (c == '\\') // Handle escaping
		{
			c = getc(stream);
			if (c == EOF)
			{
				free(str);
				return (error_out(EOF));
			}
			if (c != '"' && c != '\\')
			{
				free(str);
				return (error_out(c));
			}
		}
		// Native realloc handles the memory expansion in 3 lines
		str = realloc(str, len + 2);
		str[len] = c;
		str[len + 1] = '\0';
		len++;
	}
	free(str);
	return (error_out(EOF));
}

int	parse_map(map **dst, FILE *stream)
{
	char	*key;
	json	val;
	int		c;

	if (getc(stream) != '{')
		return (-1);
	map *m = calloc(1, sizeof(map)); // calloc sets data=NULL,
	size = 0 automatically if (peek(stream) == '}')
	{
		getc(stream); // Consume the '}'
		*dst = m;
		return (1);
	}
	while (1)
	{
		// 1. Key
		if (peek(stream) != '"')
		{
			free_map(m);
			return (error_out(getc(stream)));
		}
		if (parse_string(&key, stream) == -1)
		{
			free_map(m);
			return (-1);
		}
		// 2. Colon
		c = getc(stream);
		if (c != ':')
		{
			free(key);
			free_map(m);
			return (error_out(c));
		}
		// 3. Value
		if (parse_value(&val, stream) == -1)
		{
			free(key);
			free_map(m);
			return (-1);
		}
		// 4. Realloc the map array (realloc(NULL) acts like malloc)
		m->data = realloc(m->data, sizeof(pair) * (m->size + 1));
		m->data[m->size].key = key;
		m->data[m->size].value = val;
		m->size++;
		// 5. Delimiter
		c = getc(stream);
		if (c == '}')
		{
			*dst = m;
			return (1);
		}
		if (c != ',')
		{
			free_map(m);
			return (error_out(c));
		}
	}
}

int	parse_value(json *dst, FILE *stream)
{
	int	c;

	c = peek(stream);
	if (c == EOF)
		return (error_out(EOF));
	if (c == '"')
	{
		dst->type = STRING;
		return (parse_string(&dst->string, stream));
	}
	if (c == '{')
	{
		dst->type = MAP;
		return (parse_map(&dst->map, stream));
	}
	if (c == '-' || isdigit(c))
	{
		dst->type = INTEGER;
		if (fscanf(stream, "%d", &dst->integer) != 1)
			return (error_out(getc(stream)));
		return (1);
	}
	return (error_out(getc(stream)));
}

int	argo(json *dst, FILE *stream)
{
	int	c;

	if (parse_value(dst, stream) == -1)
		return (-1);
	c = getc(stream);
	if (c != EOF)
		return (error_out(c));
	return (1);
}
