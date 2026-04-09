#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    
    if (bytes_read <= 0 && i == 0)
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

    // ---------------------------------------------------------
    printf("\n=== TEST 1: Basic Read ('r') ===\n");
    printf("Expected: List of files in current directory\n");
    printf("--------------------------------------------\n");
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    if (fd != -1)
    {
        while ((line = get_next_line(fd)))
        {
            ft_putstr(line);
            free(line); 
        }
        close(fd);
    }
    else
        printf("Test 1 Failed: ft_popen returned -1\n");

    // ---------------------------------------------------------
    printf("\n=== TEST 2: Basic Write ('w') ===\n");
    printf("Expected: 'apple', 'mango', 'zebra' printed in alphabetical order\n");
    printf("--------------------------------------------\n");
    fd = ft_popen("sort", (char *const []){"sort", NULL}, 'w');
    if (fd != -1)
    {
        // Write unsorted data into the pipe
        write(fd, "zebra\n", 6);
        write(fd, "apple\n", 6);
        write(fd, "mango\n", 6);
        
        // Closing the write end sends EOF to 'sort', triggering it to process and print
        close(fd); 
        
        // Sleep briefly to let the child process 'sort' finish printing to the terminal 
        // before our main program prints the next test header.
        usleep(100000); 
    }
    else
        printf("Test 2 Failed: ft_popen returned -1\n");

    // ---------------------------------------------------------
    printf("\n=== TEST 3: Chaining (ls | grep .c) ===\n");
    printf("Expected: Only files containing '.c'\n");
    printf("--------------------------------------------\n");
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    if (fd != -1)
    {
        saved_stdin = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        close(fd); 

        fd = ft_popen("grep", (char *const []){"grep", ".c", NULL}, 'r');
        if (fd != -1)
        {
            while ((line = get_next_line(fd)))
            {
                printf("%s", line);
                free(line);
            }
            close(fd);
        }
        
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }

    // ---------------------------------------------------------
    printf("\n=== TEST 4: Error Handling (Invalid Type) ===\n");
    printf("Expected: ft_popen gracefully returns -1\n");
    printf("--------------------------------------------\n");
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'x');
    if (fd == -1)
        printf("Success: ft_popen correctly rejected type 'x'.\n");
    else
    {
        printf("Failure: ft_popen accepted invalid type 'x'.\n");
        close(fd);
    }

    // ---------------------------------------------------------
    printf("\n=== TEST 5: Error Handling (Invalid Command) ===\n");
    printf("Expected: Child process exits cleanly, read returns 0 bytes (no hang)\n");
    printf("--------------------------------------------\n");
    
    // Note: ft_popen itself returns a valid FD because pipe() and fork() succeed.
    // The failure happens asynchronously in the child during execvp.
    fd = ft_popen("does_not_exist", (char *const []){"does_not_exist", NULL}, 'r');
    if (fd != -1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            printf("Success: Read safely returned NULL after execvp failed.\n");
        else
        {
            printf("Failure: Read returned data: %s\n", line);
            free(line);
        }
        close(fd);
    }

    printf("\n=== ALL TESTS COMPLETED ===\n");
    return (0);
}
