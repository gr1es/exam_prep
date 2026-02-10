#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
			sort_flag = 1;
			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
		}
		i++;
		if (!str[i] && sort_flag != 0)
		{
			sort_flag = 0;
			i = 0;
		}
	}
	return (str);
}

static void	permute(char *sorted, char *res, int *used, int len, int i)
{
	int	j;

	if (i == len)
	{
		res[len] = '\0';
		puts(res);
	}
	else
	{
		j = 0;
		while (j < len)
		{
			if (used[j] == 0)
			{
				used[j] = 1;
				res[i] = sorted[j];
				permute(sorted, res, used, len, i + 1);
				used[j] = 0;
			}
			j++;
		}
	}
}

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

int	main(int argc, char *argv[])
{
	int		len;
	char	*res;
	int		*used;
	char	*sorted;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	sorted = sort_input(argv[1]);
	used = calloc(len, sizeof(int));
	res = malloc((len + 1) * sizeof(char));
	if (!used || !res)
	{
		if (used)
			free(used);
		if (res)
			free(res);
		return (1);
	}
	permute(sorted, res, used, len, 0);
	free(used);
	free(res);
	return (0);
}
