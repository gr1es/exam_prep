
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	char	*str;
	int		len;

	if (argc != 2)
		write(1, "\n", 1);
	else
	{
		str = (char *)argv[1];
		len = 0;
		while (str[len])
			len++;
		len --;
		while (len >= 0)
		{
			write(1, &str[len], 1);
			len--;
		}
		write(1, "\n", 1);
	}
	return (0);
}
