#include <stdio.h>
#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	*sort_input(char *str)
{
	int		i;
	int		sort_flag;
	char	temp;

	if (!str)
		return (NULL);
	i = 0;
	sort_flag = 0;
	while (str[i])
	{
		if (str[i + 1] != '\0' && str[i] > str[i + 1])
		{
			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
			sort_flag = 1;
		}
		i++;
		if (sort_flag == 1 && !str[i])
		{
			sort_flag = 0;
			i = 0;
		}
	}
	return (str);
}

// i = index of result string res, starting at 0
static void	permute(char *sorted, char *res, int *used, int len, int i)
{
	int	j;

	// result is fully populated!
	if (i == len)
	{
		res[len] = '\0';
		puts(res);
		return ;
	}
	else
	{
		j = 0;
		while (j < len)
		{
			// char on index j of sorted still free?
			// if not, we don't do anything with it
			if (used[j] == 0)
			{
				// declare it used for future recursions
				used[j] = 1;
				// put current character in sorted at index j
				// into res at index i
				res[i] = sorted[j];
				permute(sorted, res, used, len, i + 1);
				used[j] = 0;
			}
			j++;
		}
	}
}

int	main(int argc, char *argv[])
{
	char	*sorted;
	int		*used;
	int		len;
	char	*res;

	if (argc != 2)
		return (1);
	sorted = sort_input((char *)argv[1]);
	len = ft_strlen(sorted);
	// int array to track if chars from sorted
	// have already been used
	// boolean: 0 for free, 1 for used
	used = calloc(len, sizeof(int));
	if (!used)
		return (1);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free(used);
		return (1);
	}
	permute(sorted, res, used, len, 0);
	free(used);
	free(res);
	return (0);
}
