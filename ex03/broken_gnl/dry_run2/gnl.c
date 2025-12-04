
#include <stdlib.h> // malloc
#include <unistd.h> // read

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *to_free, char *to_keep)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!to_free)
	{
		str = malloc((ft_strlen(to_keep) + 1) * sizeof(char));
		if (!str)
			return (NULL);
		while (to_keep[i])
		{
			str[i] = to_keep[i];
			i++;
		}
		str[i] = '\0';
	}
	else
	{
		str = malloc((ft_strlen(to_free) + ft_strlen(to_keep) + 1)
				* sizeof(char));
		if (!str)
			return (NULL);
		while (to_free[i])
		{
			str[i] = to_free[i];
			i++;
		}
		while (to_keep[j])
		{
			str[i] = to_keep[j];
			i++;
			j++;
		}
		str[i] = '\0';
		free(to_free);
	}
	return (str);
}

static int	find_newline(char *str)
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

static void	free_all(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		bytes;
	char		*line;
	char		*temp;
	int			newline_i;
	int			i;

	i = 0;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
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
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free_all(stash, buffer);
			stash = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (!stash)
		{
			stash = ft_strjoin_free(NULL, buffer);
			if (!stash)
			{
				if (buffer)
					free(buffer);
				stash = NULL;
				return (NULL);
			}
		}
		else
		{
			temp = ft_strjoin_free(stash, buffer);
			if (!temp)
			{
				free_all(stash, buffer);
				stash = NULL;
				return (NULL);
			}
			stash = temp;
		}
		newline_i = find_newline(stash);
	}
	if (newline_i == -1)
	{
		free(buffer);
		temp = stash;
		stash = NULL;
		return (temp);
	}
	line = malloc((newline_i + 2) * sizeof(char));
	if (!line)
	{
		free_all(stash, buffer);
		stash = NULL;
		return (NULL);
	}
	while (i <= newline_i)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	temp = NULL;
	if (stash[newline_i + 1] != '\0')
	{
		temp = ft_strjoin_free(NULL, stash + newline_i + 1);
		if (!temp)
		{
			free_all(stash, buffer);
			stash = NULL;
			return (NULL);
		}
	}
	free(stash);
	stash = temp;
	free(buffer);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		count;

	// 1. Open a file to read
	// Make sure you create a file named "test.txt" with some text in it!
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Please create a file named 'test.txt' to test.\n");
		return (1);
	}
	count = 1;
	printf("--- STARTING READ (BUFFER_SIZE = %d) ---\n", BUFFER_SIZE);
	// 2. Loop until get_next_line returns NULL
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// We print with brackets [] to see if the \n is inside
		printf("Line %d: [%s]", count, line);
		// IMPORTANT: You must free the line returned by GNL
		free(line);
		count++;
	}
	printf("\n--- END OF FILE ---\n");
	close(fd);
	return (0);
}

