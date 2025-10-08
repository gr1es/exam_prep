

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	char	bit;
	int		i;

	i = 8;
	while (i > 0)
	{
		i--;
		bit = (octet >> i & 1) + 48;
		write(1, &bit, 1);
	}
}
