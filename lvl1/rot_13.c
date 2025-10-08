
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int				i;
	unsigned char	letter;

	if (argc != 2)
		write(1, "\n", 1);
	else
	{
		i = 0;
		while (argv[1][i])
		{
			letter = (unsigned char)argv[1][i];
			if (letter >= 'A' && letter <= 'Z')
			{
				letter += 13;
				if (letter > 'Z')
					letter -= 26;
				write(1, &letter, 1);
			}
			else if ((letter >= 'a' && letter <= 'z'))
			{
				letter += 13;
				if (letter > 'z')
					letter -= 26;
				write(1, &letter, 1);
			}
			else
				write(1, &letter, 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
