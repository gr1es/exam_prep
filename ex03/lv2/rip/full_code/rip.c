#include <stdio.h>
#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*strip_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ')')
	{
		input[i] = ' ';
		i++;
	}
	i = ft_strlen(input) - 1;
	while (i >= 0 && input[i] == '(' && input[i] != ' ')
	{
		input[i] = ' ';
		i--;
	}
	return (input);
}

// checks if solution is valid
// returns: 1 = valid; 0 = invalid
static int	validator(char *str)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			c++;
		if (str[i] == ')')
			c--;
		i++;
		// if the balance goes negative at any point,
		// a ) without a prior ( appeared --> invalid!
		if (c < 0)
			return (0);
	}
	if (c == 0)
		return (1);
	return (0);
}

// determines how many ( and ) need to be removed
static void	get_limits(char *str, int *left_remove, int *right_remove)
{
	int	i;
	int	balance;

	balance = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			balance++;
		if (str[i] == ')')
			balance--;
		if (balance < 0)
		{
			balance = 0;
			// if balance dips into negative, there is a ) without a (
			(*right_remove)++;
		}
		i++;
	}
	// if balance is not 0, there are too many (
	*left_remove = balance;
}

static void	solve(char *str, int left_rem, int right_rem, int i)
{
	if (left_rem == 0 && right_rem == 0)
	{
		if (validator(str) == 1)
			puts(str);
		return ;
	}
	while (str[i])
	{
		if (str[i] == '(' && left_rem > 0)
		{
			str[i] = ' ';
			solve(str, left_rem - 1, right_rem, i + 1);
			// revert change so checks continue with this version
			str[i] = '(';
		}
		if (str[i] == ')' && right_rem > 0)
		{
			str[i] = ' ';
			solve(str, left_rem, right_rem - 1, i + 1);
			// revert change so checks continue with this version
			str[i] = ')';
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char	*str;
	int		left_remove;
	int		right_remove;

	if (argc != 2)
		return (1);
	str = strip_input((char *)argv[1]);
	left_remove = 0;
	right_remove = 0;
	get_limits(str, &left_remove, &right_remove);
	solve(str, left_remove, right_remove, 0);
	return (0);
}
