
#include <limits.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	if (str[0] == '0')
		return (0);
	i = 0;
	neg = 0;
	res = 0;
	if (str[0] == '+')
		i++;
	if (str[0] == '-')
	{
		i++;
		neg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	if (neg == -1)
		res *= -1;
	return (res);
}
