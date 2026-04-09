#include <stdio.h>
#include <unistd.h>

int picoshell(char **cmds[]);

int main(void)
{
    // ---------------------------------------------------------
    printf("\n=== TEST 1: Single Command ===\n");
    printf("Expected: List of files in the current directory\n");
    printf("--------------------------------------------\n");
    fflush(stdout); // Flush the print buffer before forking!
    
    char *cmd1_a[] = {"ls", NULL};
    char **cmds1[] = {cmd1_a, NULL};
    
    picoshell(cmds1);

    // ---------------------------------------------------------
    printf("\n=== TEST 2: Two Commands (ls | grep .c) ===\n");
    printf("Expected: Only files ending in '.c'\n");
    printf("--------------------------------------------\n");
    fflush(stdout);
    
    char *cmd2_a[] = {"ls", NULL};
    char *cmd2_b[] = {"grep", ".c", NULL};
    char **cmds2[] = {cmd2_a, cmd2_b, NULL};
    
    picoshell(cmds2);

    // ---------------------------------------------------------
    printf("\n=== TEST 3: Subject Example (echo | cat | sed) ===\n");
    printf("Expected output: squblblb\n");
    printf("--------------------------------------------\n");
    fflush(stdout);
    
    char *cmd3_a[] = {"echo", "squalala", NULL};
    char *cmd3_b[] = {"cat", NULL};
    char *cmd3_c[] = {"sed", "s/a/b/g", NULL};
    char **cmds3[] = {cmd3_a, cmd3_b, cmd3_c, NULL};
    
    picoshell(cmds3);

    // ---------------------------------------------------------
    printf("\n=== TEST 4: Massive Pipeline (ls | grep | wc) ===\n");
    printf("Expected: A single number (count of .c files)\n");
    printf("--------------------------------------------\n");
    fflush(stdout);
    
    char *cmd4_a[] = {"ls", NULL};
    char *cmd4_b[] = {"grep", ".c", NULL};
    char *cmd4_c[] = {"wc", "-l", NULL};
    char **cmds4[] = {cmd4_a, cmd4_b, cmd4_c, NULL};
    
    picoshell(cmds4);

    // ---------------------------------------------------------
    printf("\n=== TEST 5: Error Handling (Invalid Command) ===\n");
    printf("Expected: OS error message for 'fake_cmd', program does not hang, clean exit\n");
    printf("--------------------------------------------\n");
    fflush(stdout);
    
    char *cmd5_a[] = {"ls", NULL};
    char *cmd5_b[] = {"fake_cmd_that_does_not_exist", NULL};
    char *cmd5_c[] = {"wc", "-l", NULL};
    char **cmds5[] = {cmd5_a, cmd5_b, cmd5_c, NULL};
    
    picoshell(cmds5);

    printf("\n=== ALL TESTS COMPLETED ===\n");
    return (0);
}
