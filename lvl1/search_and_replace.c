
#include <unistd.h>

static void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int argc, char const *argv[])
{
	int		i;
	char	*str;
	char	find;
	char	repl;

	if (argc != 4 || argv[2][1] != '\0' || argv[3][1] != '\0')
		write(1, "\n", 1);
	else
	{
		i = 0;
		str = (char *)argv[1];
		find = argv[2][0];
		repl = argv[3][0];
		while (str[i])
		{
			if (str[i] == find)
				str[i] = repl;
			i++;
		}
		ft_putstr(str);
		write(1, "\n", 1);
	}
	return (0);
}
