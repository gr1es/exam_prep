
#include <unistd.h>

static int	has_words(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' && s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (0);
	else
		return (1);
}

int	main(int argc, const char *argv[])
{
	int		i;
	char	*s;

	if (argc != 2 || has_words((char *)argv[1]) == 0)
		write(1, "\n", 1);
	else
	{
		i = 0;
		s = (char *)argv[1];
		while (s[i])
			i++;
		i--;
		while (i > 0 && (s[i] == ' ' || s[i] == '\t'))
			i--;
		while (i > 0 && s[i] != ' ' && s[i] != '\t')
			i--;
		i++;
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		{
			write(1, &s[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
}
