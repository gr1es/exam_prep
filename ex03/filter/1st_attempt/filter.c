
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
	int		i;
	ssize_t	bytes;
	int		bytes_matched;

	if (argc != 2)
		return (0);
	input = malloc(BUFFER_SIZE * sizeof(char));
	if (!input)
	{
		perror("Error");
		return (1);
	}
	bytes_matched = 0;
	censor = (char *)argv[1];
	while ((bytes = read(0, input, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (input[i] == censor[bytes_matched])
			{
				bytes_matched++;
				if (censor[bytes_matched] == '\0')
				{
					while (bytes_matched > 0)
					{
						write(1, "*", 1);
						bytes_matched--;
					}
				}
			}
			else
			{
				if (bytes_matched > 0)
				{
					write(1, censor, bytes_matched);
					bytes_matched = 0;
					i--;
				}
				else
					write(1, &input[i], 1);
			}
			i++;
		}
	}
	if (bytes_matched > 0)
		write(1, censor, bytes_matched);
	if (bytes == -1)
	{
		if (input)
			free(input);
		perror("Error");
		return (1);
	}
	free(input);
	return (0);
}
