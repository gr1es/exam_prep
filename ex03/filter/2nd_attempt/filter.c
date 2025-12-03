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
	censor = (char *)argv[1]; // what is to be replaced by asterisks
	while ((bytes = read(0, input, BUFFER_SIZE)) > 0)
	{
		i = 0;
		// we look through what was read, char by char
		while (i < bytes)
		{
			// is the read char from input the same as the (current index of) the censor?
			if (input[i] == censor[chars_matched])
			{
				chars_matched++;
				if (censor[chars_matched] == '\0')
				// this means: full censor string has been found!
				{
					// write as many asterisks as there are characters in the censor (= chars_matched)
					while (chars_matched > 0)
					{
						write(1, "*", 1);
						chars_matched--; // chars_matched should be == 0 again
					}
				}
			}
			// scenario B: no match between input and censor
			else
			{
				// if there were matches before,
				// the skipped chars have to be printed
				if (chars_matched > 0)
				{
					write(1, censor, chars_matched);
					// write all the characters we skipped since they were part of censor
					chars_matched = 0; // important reset,
										// so we can start looking for censor from the start again
					i--;
					// will be incremented later; has to be decremented here so that the current char in input is not skipped
				}
				// no prior matches? just print the char
				else
					write(1, &input[i], 1);
			}
			// let's look at the next character in input, if there is one
			i++;
		}
	}
	// error handling should read fail
	if (bytes == -1)
	{
		free(input);
		perror("Error");
		return (1);
	}
	// should input end without null without newline, read returns 0,
	// loop exits and input is not compared to censor
	// --> "remainder" has to be written
	if (chars_matched > 0)
		write(1, censor, chars_matched);
	free(input);
	return (0);
}
