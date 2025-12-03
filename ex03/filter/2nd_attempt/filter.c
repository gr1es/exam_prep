#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	main(int argc, char *argv[])
{
	char	*input;
	char	*censor;
	ssize_t	bytes;
	int		i;
	int		chars_matched;

	if (argc != 2)
		return (0);
	input = malloc(BUFFER_SIZE * sizeof(char));
	if (!input)
	{
		perror("Error");
		return (1);
	}
	i = 0;
	chars_matched = 0;
	censor = (char *)argv[1];
	while ((bytes = read(0, input, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (input[i] == censor[chars_matched])
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
					write(1, &input[i], 1);
			}
			i++;
		}
	}
	if (bytes == -1)
	{
		free(input);
		perror("Error");
		return (1);
	}
	if (chars_matched > 0)
		write(1, censor, chars_matched);
	free(input);
	return (0);
}
