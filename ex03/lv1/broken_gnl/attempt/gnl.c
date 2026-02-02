
#include <stdlib.h>
#include <unistd.h>

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
	int		i;
	int		j;
	char	*str;

	i = 0;
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
		j = 0;
		while (to_keep[j])
		{
			str[i] = to_keep[j];
			i++;
			j++;
		}
		str[i] = '\0';
	}
	return (str);
}

static int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static void	freer(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*temp;
	char		*line;
	char		*buffer;
	int			i;
	int			newline_i;
	ssize_t		bytes;

	i = 0;
	newline_i = find_newline(stash);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		freer(stash, NULL);
		stash = NULL;
		return (NULL);
	}
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
			break ;
		buffer[bytes] = '\0';
		if (!stash)
		{
			stash = ft_strjoin_free(NULL, buffer);
			if (!stash)
			{
				freer(NULL, buffer);
				stash = NULL;
				return (NULL);
			}
		}
		else
		{
			temp = ft_strjoin_free(stash, buffer);
			if (!temp)
			{
				freer(stash, buffer);
				stash = NULL;
				return (NULL);
			}
			stash = temp;
		}
		newline_i = find_newline(stash);
	}
	if (newline_i == -1)
	{
		line = stash;
		stash = NULL;
		freer(NULL, buffer);
		return (line);
	}
	line = malloc((newline_i + 1 + 1) * sizeof(char));
	if (!line)
	{
		freer(buffer, stash);
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
			freer(stash, buffer);
			freer(NULL, line);
			stash = NULL;
			return (NULL);
		}
	}
	freer(stash, NULL);
	stash = temp;
	temp = NULL;
	freer(NULL, buffer);
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
