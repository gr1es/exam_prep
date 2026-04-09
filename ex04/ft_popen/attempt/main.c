#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Your ft_popen implementation goes here
int ft_popen(const char *file, char *const argv[], char type);

// Simple ft_putstr for testing
void ft_putstr(char *str)
{
    if (!str)
        return;
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}

// Quick and dirty get_next_line for testing
char *get_next_line(int fd)
{
    char *line;
    char c;
    int i = 0;
    int bytes_read;

    if (fd < 0)
        return (NULL);
        
    line = malloc(10000); 
    if (!line)
        return (NULL);

    while ((bytes_read = read(fd, &c, 1)) > 0)
    {
        line[i++] = c;
        if (c == '\n')
            break;
    }
    
    if (bytes_read < 0 || (bytes_read == 0 && i == 0))
    {
        free(line);
        return (NULL);
    }
    
    line[i] = '\0';
    return (line);
}

int main(void)
{
    int  fd;
    char *line;
    int  saved_stdin;

    printf("--- Test 1: ft_popen(\"ls\", ..., 'r') ---\n");
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    
    if (fd == -1)
    {
        printf("Test 1 Error: ft_popen failed to launch 'ls'.\n");
    }
    else
    {
        while ((line = get_next_line(fd)))
        {
            ft_putstr(line);
            free(line); 
        }
        close(fd);
    }

    printf("\n--- Test 2: ls | grep c ---\n");
    
    // Step 2a: Launch ls
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    if (fd == -1)
    {
        printf("Test 2 Error: ft_popen failed to launch initial 'ls'.\n");
        return (1);
    }

    // Save original stdin so we can restore it later, keeping the program stable
    saved_stdin = dup(0);
    
    // Redirect ls output (fd) to standard input (0)
    dup2(fd, 0);
    close(fd); // We can close the original fd now that 0 is pointing to it

    // Step 2b: Launch grep
    // Grep will read from 0, which is now receiving data from the 'ls' pipe
    fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
    if (fd == -1)
    {
        printf("Test 2 Error: ft_popen failed to launch 'grep'.\n");
        
        // Cleanup before exiting
        dup2(saved_stdin, 0);
        close(saved_stdin);
        return (1);
    }

    // Read the final output from grep
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);

    // Restore standard input to normal
    dup2(saved_stdin, 0);
    close(saved_stdin);

    printf("\n--- Tests Complete ---\n");
    return (0);
}
