
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int		i;
	char	*str;
	int		repeats;

	if (argc != 2)
		write(1, "\n", 1);
	else
	{
		i = 0;
		str = (char *)argv[1];
		while (str[i])
		{
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z'))
			{
				if (str[i] >= 'a' && str[i] <= 'z')
					repeats = str[i] - 96;
				else
					repeats = str[i] - 64;
				while (repeats != 0)
				{
					write(1, &str[i], 1);
					repeats--;
				}
			}
			else
				write(1, &str[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
