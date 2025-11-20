
#include <stdio.h>
#include <unistd.h>

static int	g_bytes;

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	while (str[i])
	{
		write(1, &str[i], fd);
		i++;
	}
}

static int	check_format(const char *str)
{
	int	i;
	int	dir_nbr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			dir_nbr++;
		i++;
	}
	return (dir_nbr);
}

int	ft_printf(const char *format, ...)
{
	int	dir_nbr;

	g_bytes = 0;
	dir_nbr = 0;
	dir_nbr = check_format(format);
	if (dir_nbr < 0)
		return (-1);
	if (dir_nbr == 0)
	{
		ft_putstr_fd(format, 1);
		return (ft_strlen(format));
	}
}

int	main(void)
{
	char	*str;
	int		result_ft;
	int		result_org;

	// str = "print:\n%%s: %s\n%%d: %d\n%%x: %x\n\n";
	str = "This string has no directives.\n";
	printf("ft:\n");
	printf("ft return: %i\n\n\n", ft_printf(str, "Hello World!", 123456,
			123456));
	// \n, \t also needs testing!
	printf("org:\n");
	printf("org return: %i\n\n\n", printf(str, "Hello World!", 123456, 123456));
}
