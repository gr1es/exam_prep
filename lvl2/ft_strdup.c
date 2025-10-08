
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}
