
#include <unistd.h>

int	is_part(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	s[i] = c;
	s[i + 1] = '\0';
	return (0);
}

int	main(int argc, const char *argv[])
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;
	char	done[120];

	if (argc != 3)
		write(1, "\n", 1);
	else
	{
		s1 = (char *)argv[1];
		s2 = (char *)argv[2];
		i = 0;
		while (s1[i])
		{
			j = 0;
			while (s2[j])
			{
				if (s1[i] == s2[j])
				{
					if (is_part(s1[i], done) == 0)
						write(1, &s1[i], 1);
				}
				j++;
			}
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
