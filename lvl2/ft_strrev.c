
char	*ft_strrev(char *str)
{
	char	temp;
	int		len;
	int		i;

	len = 0;
	while (str[len])
		len++;
	len--;
	i = 0;
	while (i < len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
	return (str);
}
