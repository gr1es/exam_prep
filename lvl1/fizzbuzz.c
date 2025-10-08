
#include <unistd.h>

static void	ft_put_nbr(int nbr)
{
	char	nbr_char;
	
	if (nbr > 9)
		ft_put_nbr(nbr / 10);
	nbr_char = (nbr % 10)  + 48;
	write(1, &nbr_char, 1);
}

int	main(int argc, char const *argv[])
{
	int		nbr;

	nbr = 1;
	while (nbr <= 100)
	{
		if (nbr % 3 == 0)
			write(1, "fizz", 5);
		if (nbr % 5 == 0)
			write(1, "buzz", 5);
		if (nbr % 3 != 0 && nbr % 5 != 0)
			ft_put_nbr(nbr);
		write(1, "\n", 1);
		nbr++;
	}
	return (0);
}
