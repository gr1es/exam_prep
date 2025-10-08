
#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	res;
	int		j;

	res = 0;
	while (s[res])
	{
		j = 0;
		while (reject[j])
		{
			if (s[res] == reject[j])
				return (res);
			j++;
		}
		res++;
	}
	return (res);
}
