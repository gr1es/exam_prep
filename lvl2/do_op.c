
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int	n1;
	int	n2;

	if (argc != 4)
		printf("\n");
	else
	{
		n1 = atoi(argv[1]);
		n2 = atoi(argv[3]);
		if (argv[2][0] == '+')
			printf("%i\n", n1 + n2);
		else if (argv[2][0] == '-')
			printf("%i\n", n1 - n2);
		else if (argv[2][0] == '*')
			printf("%i\n", n1 * n2);
		else if (argv[2][0] == '/')
			printf("%i\n", n1 / n2);
		else if (argv[2][0] == '%')
			printf("%i\n", n1 % n2);
	}
	return (0);
}
