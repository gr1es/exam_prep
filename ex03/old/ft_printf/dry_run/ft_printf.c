
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
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

static int	count_digits(int nbr)
{
	int	digits;

	digits = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		digits++;
	}
	return (digits);
}
static int	print_int(int nbr)
{
	char	c;
	int		digits;
	int		quot;
	int		result;

	result = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr == INT_MIN)
		return (ft_putstr_fd("-2147483648", 1));
	if (nbr < 0)
	{
		nbr *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		result++;
	}
	digits = count_digits(nbr);
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

static char	*reverse_string(char *str)
{
	int		i;
	int		end;
	char	temp;

	i = 0;
	end = ft_strlen(str) - 1;
	while (i < end)
	{
		temp = str[i];
		str[i] = str[end];
		str[end] = temp;
		i++;
		end--;
	}
	return (str);
}

static char	*int_to_hex_str(unsigned int nbr)
{
	char	*str;
	int		i;
	int		mod;

	i = 0;
	str = malloc(9 * sizeof(char));
	if (!str)
		return (NULL);
	while (nbr != 0)
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
	return (reverse_string(str));
}

static int	print_hex(unsigned int nbr)
{
	char	*str;
	int		result;

	if (nbr == 0)
		return (ft_putstr_fd("0", 1));
	str = int_to_hex_str(nbr);
	result = ft_putstr_fd(str, 1);
	free(str);
	return (result);
}

static int	handle_dir(const char dir, va_list arg_list)
{
	int	g_bytes_temp;

	g_bytes_temp = g_bytes;
	if (dir == '%')
		g_bytes += write(1, "\%", 1);
	else if (dir == 's')
		g_bytes += ft_putstr_fd(va_arg(arg_list, char *), 1);
	else if (dir == 'd' || dir == 'i')
		g_bytes += print_int(va_arg(arg_list, int));
	else if (dir == 'x')
		g_bytes += print_hex(va_arg(arg_list, unsigned int));
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
	va_list	arg_list;

	g_bytes = 0;
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
	ft_printf("Magic %s is %d\n", "number", 42);
	return (0);
}

// void	test_str(char *s)
// {
// 	int	r_org;
// 	int	r_ft;

// 	printf("--------------------------------------\n");
// 	printf("TEST: %%s with [%s]\n", s);
// 	printf("ORG: ");
// 	fflush(stdout);
// 	r_org = printf("%s", s);
// 	printf("\n");
// 	printf(" FT: ");
// 	fflush(stdout);
// 	r_ft = ft_printf("%s", s);
// 	printf("\n");
// 	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
// 	if (r_org == r_ft)
// 		printf("RESULT: OK\n");
// 	else
// 		printf("RESULT: FAIL\n");
// 	printf("\n");
// }

// void	test_int(int d)
// {
// 	int	r_org;
// 	int	r_ft;

// 	printf("--------------------------------------\n");
// 	printf("TEST: %%d with [%d]\n", d);
// 	printf("ORG: ");
// 	fflush(stdout);
// 	r_org = printf("%d", d);
// 	printf("\n");
// 	printf(" FT: ");
// 	fflush(stdout);
// 	r_ft = ft_printf("%d", d);
// 	printf("\n");
// 	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
// 	if (r_org == r_ft)
// 		printf("RESULT: OK\n");
// 	else
// 		printf("RESULT: FAIL\n");
// 	printf("\n");
// }

// void	test_hex(unsigned int x)
// {
// 	int	r_org;
// 	int	r_ft;

// 	printf("--------------------------------------\n");
// 	printf("TEST: %%x with [%u]\n", x);
// 	printf("ORG: ");
// 	fflush(stdout);
// 	r_org = printf("%x", x);
// 	printf("\n");
// 	printf(" FT: ");
// 	fflush(stdout);
// 	r_ft = ft_printf("%x", x);
// 	printf("\n");
// 	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
// 	if (r_org == r_ft)
// 		printf("RESULT: OK\n");
// 	else
// 		printf("RESULT: FAIL\n");
// 	printf("\n");
// }

// int	main(void)
// {
// 	// 1. STRINGS
// 	test_str("Hello");
// 	test_str("");
// 	test_str(NULL);
// 	// 2. INTEGERS
// 	test_int(42);
// 	test_int(-42);
// 	test_int(0);
// 	test_int(INT_MAX);
// 	test_int(INT_MIN);
// 	// 3. HEX
// 	test_hex(42);
// 	test_hex(0);
// 	test_hex(INT_MAX);
// 	test_hex(UINT_MAX);
// 	return (0);
// }
