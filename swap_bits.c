
#include <stdio.h>

unsigned char	swap_bits(unsigned char octet)
{
	return (octet >> 4 | octet << 4);
}

int	main(void)
{
	unsigned char	bit;
	unsigned char	res;
	int				i;

	bit = 0;
	// by changing the number on the next line, you change
	// the bits that are sent to the reverse_bits function
	// 5 => 0000 0101, the result should be 1010 0000
	res = swap_bits((unsigned char)5);
	i = 8;
	while (i--)
	{
		bit = (res >> i & 1) + 48;
		printf("%c", bit);
	}
	printf("\n");
}
