#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ANSI Color Codes
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

// Function to convert a positive decimal integer to its MINIMAL binary string representation.
char *to_binary_string(int n) {
    static char binary[9]; 
    int i = 7; 

    if (n == 0) {
        strcpy(binary, "0");
        return binary;
    }

    memset(binary, '0', 8);
    binary[8] = '\0'; 
    
    while (n > 0 && i >= 0) {
        binary[i] = (n % 2) + '0';
        n /= 2;
        i--;
    }
    
    i = 0;
    while (binary[i] == '0' && binary[i + 1] != '\0') {
        i++;
    }
    
    return &binary[i]; 
}

int main() {
    int current_number = 0;
    const int MAX_NUMBER = 100; 
    char user_input[10]; 

    printf("Welcome to the Binary Input Quiz (0 to %d).\n", MAX_NUMBER);
    printf("Please enter the MINIMAL binary string (e.g., 10 is 1010).\n");
    printf("----------------------------------------------------------\n");

    while (current_number <= MAX_NUMBER) {
        
        char *correct_binary = to_binary_string(current_number);
        int attempts = 0;
        
        printf("Decimal: %d\n", current_number);

        while (attempts < 3) {
            // Prompt and read user input
            printf("Attempt %d/3 - Enter the binary value: ", attempts + 1);
            
            if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
                return 0; 
            }

            // Remove newline
            user_input[strcspn(user_input, "\n")] = 0;
            
            // Print user input in BLUE for feedback
            printf(COLOR_BLUE "%s" COLOR_RESET "\n", user_input); 

            // Check if the input is correct
            if (strcmp(user_input, correct_binary) == 0) {
                // Success message in GREEN
                printf(COLOR_GREEN "--> CORRECT! Proceeding to %d." COLOR_RESET "\n\n", current_number + 1);
                break; 
            } else {
                attempts++;
                if (attempts < 3) {
                    // Failure message in RED
                    printf(COLOR_RED "--> Incorrect. Try again." COLOR_RESET "\n");
                }
            }
        }
        
        // Handle failure after 3 attempts
        if (attempts == 3) {
            // Failure block messages in RED
            printf(COLOR_RED "\n--- FAILED ---" COLOR_RESET "\n");
            printf(COLOR_RED "The correct binary for %d was: %s" COLOR_RESET "\n", current_number, correct_binary);
            printf(COLOR_RED "Progress reset. Moving to %d." COLOR_RESET "\n", current_number + 1);
            printf(COLOR_RED "--------------" COLOR_RESET "\n\n");
        }
        
        current_number++;
    }

    printf("Quiz complete. Final number reached: %d.\n", MAX_NUMBER);
    return 0;
}
