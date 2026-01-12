
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	main(int argc, char *argv[])
{
	int		i;
	ssize_t	chars_matched;
	char	*to_censor;
	char	*line;
	ssize_t	bytes;

	if (argc != 2)
		return (0);
	to_censor = (char *)argv[1];
	chars_matched = 0;
	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
		return (1);
	while ((bytes = read(0, line, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (line[i] == to_censor[chars_matched])
			{
				chars_matched++;
				if (to_censor[chars_matched] == '\0')
				{
					while (chars_matched > 0)
					{
						write(1, "*", 1);
						chars_matched--;
					}
				}
			}
			else
			{
				if (chars_matched > 0)
				{
					write(1, to_censor, chars_matched);
					chars_matched = 0;
					i--;
				}
				else
					write(1, &line[i], 1);
			}
			i++;
		}
	}
	if (bytes == -1)
	{
		if (line)
			free(line);
		return (1);
	}
	if (chars_matched > 0)
		write(1, to_censor, chars_matched);
	if (line)
		free(line);
	return (0);
}
