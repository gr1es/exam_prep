

#include <limits.h> // for INT_MIN/INT_MAX
#include <stdarg.h> // for va_ stuff
#include <stdlib.h> // for malloc/free
#include <unistd.h> // for write

static int	g_bytes = 0;

static int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (-1);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr_fd("(null)", 1));
	while (str[i])
	{
		if (write(fd, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (ft_strlen(str));
}

static int	check_input(const char *format)
{
	int	i;
	int	dir;

	if (!format)
		return (-1);
	if (format[0] == '\0')
		return (0);
	i = 0;
	dir = 0;
	while (format[i])
	{
		if (format[i] == '%')
			dir++;
		i++;
	}
	if (dir == 0)
		return (0);
	return (1);
}

static char	*reverse_str(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[end];
		str[end] = str[start];
		str[start] = temp;
		end--;
		start++;
	}
	return (str);
}

static int	print_int(int n)
{
	int		i;
	int		nbr;
	char	str[12];

	if (n == 0)
		return (ft_putstr_fd("0", 1));
	if (n == INT_MAX)
		return (ft_putstr_fd("2147483647", 1));
	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", 1));
	i = 0;
	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		str[i] = (nbr % 10) + 48;
		nbr /= 10;
		i++;
	}
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	return (ft_putstr_fd(reverse_str(str), 1));
}

static char	*int_to_hex_str(unsigned int nbr)
{
	char			*str;
	int				i;
	unsigned int	mod;

	str = malloc(9 * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (nbr > 0)
	{
		mod = nbr % 16;
		if (mod < 10)
			str[i] = mod + 48;
		else
			str[i] = mod + 87;
		nbr /= 16;
		i++;
	}
	str[i] = '\0';
	return (reverse_str(str));
}

static int	print_hex(unsigned int nbr)
{
	char	*str;
	int		result;

	if (nbr == 0)
		return (ft_putstr_fd("0", 1));
	str = int_to_hex_str(nbr);
	if (!str)
		return (-1);
	result = ft_putstr_fd(str, 1);
	free(str);
	return (result);
}

static int	print_dir(char dir, va_list arg_list)
{
	int	bytes_temp;

	bytes_temp = g_bytes;
	if (dir == '%')
		g_bytes += ft_putstr_fd("%", 1);
	if (dir == 's')
		g_bytes += ft_putstr_fd(va_arg(arg_list, char *), 1);
	if (dir == 'd' || dir == 'i')
		g_bytes += print_int(va_arg(arg_list, int));
	if (dir == 'x')
		g_bytes += print_hex(va_arg(arg_list, unsigned int));
	if (bytes_temp > g_bytes)
		return (-1);
	return (1);
}

static int	handle_dir(const char *format, va_list arg_list)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			{
				g_bytes++;
				if (write(1, &format[i], 1) == -1)
					return (-1);
			}
		}
		else
		{
			i++;
			if (format[i] == '\0' || print_dir(format[i], arg_list) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		input;

	g_bytes = 0;
	input = check_input(format);
	if (input == 0)
		return (ft_putstr_fd(format, 1));
	if (input == -1)
		return (-1);
	va_start(arg_list, format);
	if (handle_dir(format, arg_list) == -1)
		g_bytes = -1;
	va_end(arg_list);
	return (g_bytes);
}
