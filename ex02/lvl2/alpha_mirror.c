
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int		i;
	char	*str;
	int		diff;
	char	letter;

	if (argc != 2)
		write(1, "\n", 1);
	else
	{
		i = 0;
		str = (char *)argv[1];
		while (str[i])
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				diff = 90 - str[i];
				letter = 65 + diff;
				write(1, &letter, 1);
			}
			else if (str[i] >= 'a' && str[i] <= 'z')
			{
				diff = 122 - str[i];
				letter = 97 + diff;
				write(1, &letter, 1);
			}
			else
				write(1, &str[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
