
int	max(int *tab, unsigned int len)
{
	int	res;
	int	i;

	if (len > 0)
	{
		res = tab[0];
		i = 0;
		while (i < len)
		{
			if (res < tab[i])
				res = tab[i];
			i++;
		}
		return (res);
	}
	return (0);
}

#include <stdio.h>

int	main(void)
{
	int	int_tab[] = {-1, -3, -2, -10, -9};

	printf("%d", max(int_tab, 5));
}
