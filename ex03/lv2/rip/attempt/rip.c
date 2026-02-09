#include <stdio.h>
#include <unistd.h>

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

static char	*strip_input(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ')')
	{
		str[i] = ' ';
		i++;
	}
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == '(')
	{
		str[i] = ' ';
		i--;
	}
	return (str);
}

static int	validator(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '(')
			c++;
		if (str[i] == ')')
			c--;
		if (c < 0)
			return (0);
		i++;
	}
	if (c != 0)
		return (0);
	return (1);
}

static void	get_limits(char *str, int *left_rem, int *right_rem)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	*left_rem = 0;
	*right_rem = 0;
	while (str[i])
	{
		if (str[i] == '(')
			c++;
		if (str[i] == ')')
			c--;
		if (c < 0)
		{
			(*right_rem)++;
			c = 0;
		}
		i++;
	}
	*left_rem = c;
}

static void	solve(char *str, int left_rem, int right_rem, int i)
{
	if (right_rem == 0 && left_rem == 0)
	{
		if (validator(str) == 1)
			puts(str);
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '(' && left_rem > 0)
			{
				str[i] = ' ';
				solve(str, left_rem - 1, right_rem, i + 1);
				str[i] = '(';
			}
			else if (str[i] == ')' && right_rem > 0)
			{
				str[i] = ' ';
				solve(str, left_rem, right_rem - 1, i + 1);
				str[i] = ')';
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	char	*str;
	int		left_rem;
	int		right_rem;

	if (argc != 2)
		return (1);
	str = strip_input((char *)argv[1]);
	left_rem = 0;
	right_rem = 0;
	get_limits(str, &left_rem, &right_rem);
	solve(str, left_rem, right_rem, 0);
	return (0);
}
