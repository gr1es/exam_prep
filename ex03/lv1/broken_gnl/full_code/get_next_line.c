#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static int  ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

static char *ft_strjoin_free(char *to_free, char *to_keep)
{
    int     i;
    int     j;
    char    *str;

    if (!to_free)
    {
        str = malloc((ft_strlen(to_keep) + 1) * sizeof(char));
        if (!str)
            return (NULL);
        i = 0;
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
            return (NULL); // Note: In this specific implementation, to_free is NOT freed if malloc fails here.
                           // This is handled by free_all in GNL.
        i = 0;
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
        free(to_free);
    }
    return (str);
}

static int  find_newline(char *str)
{
    int i;

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

static void free_all(char *stash, char *buffer)
{
    if (stash)
        free(stash);
    if (buffer)
        free(buffer);
}

char    *get_next_line(int fd)
{
    int         i;
    static char *stash;
    char        *buffer;
    ssize_t     bytes;
    char        *temp;
    int         newline_i;
    char        *line;

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
    {
        free_all(stash, NULL);
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
                free_all(stash, buffer);
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
                stash = NULL; // FIX 1: Prevent dangling pointer
                return (NULL);
            }
            stash = temp;
        }
        newline_i = find_newline(stash);
    }
    if (newline_i == -1)
    {
        if (buffer)
            free(buffer);
        temp = stash;
        stash = NULL;
        return (temp);
    }
    line = malloc((newline_i + 1 + 1) * sizeof(char));
    if (!line)
    {
        free_all(stash, buffer);
        stash = NULL;
        return (NULL);
    }
    i = 0;
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
            free(line); // FIX 2: Prevent leak of 'line' on error
            return (NULL);
        }
    }
    free(stash);
    stash = temp;
    free(buffer);
    return (line);
}

// tester main

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    char    *line;
    int     fd;
    int     count;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Please create a file named 'test.txt' to test.\n");
        return (1);
    }
    count = 1;
    printf("--- STARTING READ (BUFFER_SIZE = %d) ---\n", BUFFER_SIZE);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        printf("Line %d: [%s]", count, line);
        free(line);
        count++;
    }
    printf("\n--- END OF FILE ---\n");
    if (line)
        free(line);
    close(fd);
    return (0);
}
