
#include <stddef.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	res;
	size_t	j;

	res = 0;
	while (s[res])
	{
		j = 0;
		while (accept[j] != '\0')
		{
			if (s[res] == accept[j])
			{
				res++;
				break ;
			}
			j++;
		}
		if (accept[j] == '\0')
			break ;
	}
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char		*s;
// 	const char	*accept = "jfkhpell";

// 	s = "hello";
// 	printf("%zu\n", ft_strspn(s, accept));
// }
