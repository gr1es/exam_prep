

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	res;
	int				i;

	i = 8;
	res = 0;
	while (i > 0)
	{
		res = res << 1;
		res = res | (octet & 1);
		octet = octet >> 1;
		i--;
	}
	return (res);
}
