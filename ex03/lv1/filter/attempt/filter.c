
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	main(int argc, char *argv[])
{
	char	*line;
	char	*censor;
	int		i;
	int		chars_matched;
	ssize_t	bytes;

	if (argc != 2)
		return (1);
	censor = (char *)argv[1];
	chars_matched = 0;
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (1);
	while ((bytes = read(0, line, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (line[i] == censor[chars_matched])
			{
				chars_matched++;
				if (censor[chars_matched] == '\0')
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
					write(1, censor, chars_matched);
					chars_matched = 0;
					i--;
				}
				else
					write(1, &line[i], 1);
			}
			i++;
		}
	}
	free(line);
	if (bytes == -1)
		return (1);
	return (0);
	if (chars_matched > 0)
		write(1, censor, chars_matched);
	return (0);
}
