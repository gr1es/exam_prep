
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static int	g_bytes = 0;

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (write(1, &str[i], fd) == -1)
			return (-1);
		i++;
	}
	return (ft_strlen(str));
}

static int	count_dir(const char *str)
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

static int	print_int(int nbr)
{
	char	c;
	int		nbr_temp;
	int		digits;
	int		quot;
	int		result;

	result = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr < 0)
	{
		nbr *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		result++;
	}
	nbr_temp = nbr;
	digits = 0;
	while (nbr_temp > 0)
	{
		nbr_temp /= 10;
		digits++;
	}
	quot = 1;
	result += digits;
	while ((digits - 1) > 0)
	{
		quot *= 10;
		digits--;
	}
	while (quot > 0)
	{
		c = ((nbr / quot) % 10) + 48;
		if (write(1, &c, 1) == -1)
			return (-1);
		quot /= 10;
	}
	return (result);
}

static int	handle_dir(const char dir, va_list arg_list)
{
	int	g_bytes_temp;

	g_bytes_temp = g_bytes;
	if (dir == '%')
		g_bytes += write(1, "\%", 1);
	else if (dir == 's')
	{
		g_bytes += ft_putstr_fd(va_arg(arg_list, char *), 1);
	}
	else if (dir == 'd' || dir == 'i')
		g_bytes += print_int(va_arg(arg_list, int));
	if (g_bytes < g_bytes_temp)
		return (-1);
	return (0);
}

static int	print_format(const char *str, va_list arg_list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			if (write(1, &str[i], 1) == -1)
				return (-1);
			g_bytes++;
		}
		else
		{
			if (handle_dir(str[i + 1], arg_list) == -1)
				return (-1);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		dir_nbr;
	char	**array;
	va_list	arg_list;

	g_bytes = 0;
	dir_nbr = 0;
	dir_nbr = count_dir(format);
	if (dir_nbr == 0)
	{
		if (ft_putstr_fd(format, 1) == -1)
			return (-1);
		return (ft_strlen(format));
	}
	va_start(arg_list, format);
	if (print_format(format, arg_list) == -1)
	{
		va_end(arg_list);
		return (-1);
	}
	va_end(arg_list);
	return (g_bytes);
}

///////////////////////////////////////////

int	main(void)
{
	char	*str;
	int		result_ft;
	int		result_org;

	printf("\n\norg:\n");
	result_org = printf("%%s: %s\n%%d: %d\n\n", "Hello World!", 7384);
	printf("org return: %i\n\n", result_org);
	printf("__________\n\n\n");
	printf("ft:\n");
	result_ft = ft_printf("%%s: %s\n%%d: %d\n\n", "Hello World!", 7384);
	printf("ft return: %i\n\n\n", result_ft);
	return (0);
}
