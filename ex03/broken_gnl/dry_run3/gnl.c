
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin_free(char *to_free, char *to_keep)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc((ft_strlen(to_free) + ft_strlen(to_keep) + 1)
			* sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	if (!to_free)
	{
		while (to_keep[i])
		{
			joined[i] = to_keep[i];
			i++;
		}
	}
	else
	{
		while (to_free[i])
		{
			joined[i] = to_free[i];
			i++;
		}
		free(to_free);
		while (to_keep[j])
		{
			joined[i] = to_keep[j];
			i++;
			j++;
		}
	}
	joined[i] = '\0';
	return (joined);
}

int	find_newline(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	freer(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			i;
	int			newline_i;
	ssize_t		bytes;
	char		*line;
	char		*buffer;
	char		*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	newline_i = find_newline(stash);
	while (newline_i == -1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			freer(buffer, stash);
			stash = NULL;
			return (NULL);
		}
		if (bytes == 0)
		{
			if (!stash)
			{
				free(buffer);
				stash = NULL;
				return (NULL);
			}
			else
			{
				line = stash;
				stash = NULL;
				free(buffer);
				return (line);
			}
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin_free(stash, buffer);
		if (!stash)
		{
			stash = NULL;
			freer(buffer, NULL);
			return (NULL);
		}
		newline_i = find_newline(stash);
	}
	line = malloc((newline_i + 1 + 1) * sizeof(char));
	i = 0;
	while (i <= newline_i)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	temp = ft_strjoin_free(NULL, stash + newline_i + 1);
	if (!temp)
	{
		freer(stash, buffer);
		stash = NULL;
		return (NULL);
	}
	free(stash);
	stash = temp;
	free(buffer);
	return (line);
}

// tester main

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		count;
	int i = 0;

	// 1. Open a file to read
	// Make sure you create a file named "test.txt" with some text in it!
	fd = open("../full_code/test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Please create a file named 'test.txt' to test.\n");
		return (1);
	}
	count = 1;
	printf("--- STARTING READ (BUFFER_SIZE = %d) ---\n", BUFFER_SIZE);
	// 2. Loop until get_next_line returns NULL
	while (i < 3)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// We print with brackets [] to see if the \n is inside
		printf("Line %d: [%s]", count, line);
		// IMPORTANT: You must free the line returned by GNL
		free(line);
		count++;
		i++;
	}
	printf("\n--- END OF FILE ---\n");
	close(fd);
	return (0);
}
