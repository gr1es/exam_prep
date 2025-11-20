
void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int	a;
	int	b;

	a = 4;
	b = 2;
	ft_swap(&a, &b);
	printf("a: %i\nb: %i\n", a, b);
	return (0);
}
