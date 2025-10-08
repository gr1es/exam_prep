
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int		i;
	char	*str;
	char	letter;


	if (argc != 2)
		return (1);
	else
	{
		i = 0;
		str = (char *)argv[1];
		while (str[i])
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				write(1, "_", 1);
				letter = str[i] + 32;
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
