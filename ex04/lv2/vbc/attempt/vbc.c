
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int	level_1(char *str, int *i);

static void	error_msg(char c)
{
	if (c == '\0')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
	exit(1);
}

static int	level_3(char *str, int *i)
{
	int	res;

	if (str[*i] == '(')
	{
		(*i)++;
		res = level_1(str, i);
		if (str[*i] == ')')
			(*i)++;
		else
			error_msg(str[*i]);
		return (res);
	}
	else if (isdigit(str[*i]))
	{
		res = str[*i] - 48;
		(*i)++;
		return (res);
	}
	else
		error_msg(str[*i]);
	return (0);
}

static int	level_2(char *str, int *i)
{
	int	res;

	res = level_3(str, i);
	while (str[*i] == '*')
	{
		(*i)++;
		res *= level_3(str, i);
	}
	return (res);
}

static int level_1(char *str, int *i)

{
	int	res;

	res = level_2(str, i);
	while (str[*i] == '+')
	{
		(*i)++;
		res += level_2(str, i);
	}
	return (res);
}

int main (int argc, char **argv)
{
	int i;
	char *str;
	int res;

	if (argc != 2)
		return (1);
	i = 0;
	str = argv[1];
	res = level_1(str, &i);
	if (str[i] != '\0')
		error_msg(str[i]);
	printf("%i\n", res);
	return (0);
}
