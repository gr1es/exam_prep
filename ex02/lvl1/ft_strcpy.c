
char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}


#include <stdio.h>
#include <stddef.h> // Include this for size_t (optional, but good practice)

// --- REMINDER ---
// Your implementation of ft_strcpy must be available when compiling this main.
// For example, if you are using a header file (ft_string.h), include it here.

#define MAX_SIZE 20
#define TEST_STRING_A "Hello, 42!"
#define TEST_STRING_B "" // Empty string
#define TEST_STRING_C "Just sixteen chars" // 18 chars including '\0'

// A simplified, safe version of strcmp (for comparison only)
int local_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int main()
{
    // The size of the destination buffer must be large enough to hold the source string plus the null terminator.
    char dest1[MAX_SIZE]; 
    char dest2[MAX_SIZE];
    
    printf("--- Testing ft_strcpy ---\n");
    printf("Destination Buffer Size: %d bytes\n", MAX_SIZE);
    
    // Case 1: Standard copy
    printf("\n[Case 1: Standard Copy]\n");
    printf("Source: \"%s\"\n", TEST_STRING_A);
    
    // 🧠 Call YOUR function
    ft_strcpy(dest1, TEST_STRING_A); 
    
    printf("Result: \"%s\"\n", dest1);
    
    // Verification
    if (local_strcmp(dest1, TEST_STRING_A) == 0)
        printf("✅ SUCCESS: Destination matches source.\n");
    else
        printf("❌ FAILURE: Destination does NOT match source.\n");

    // Case 2: Copying an Empty String
    printf("\n[Case 2: Empty String Source]\n");
    printf("Source: \"%s\"\n", TEST_STRING_B);
    
    // 🧠 Call YOUR function
    ft_strcpy(dest2, TEST_STRING_B);
    
    printf("Result: \"%s\"\n", dest2);
    
    // Verification
    if (local_strcmp(dest2, TEST_STRING_B) == 0)
        printf("✅ SUCCESS: Destination is correctly empty.\n");
    else
        printf("❌ FAILURE: Destination is NOT empty.\n");

    // Case 3: Testing the Return Value (Should return a pointer to the destination)
    printf("\n[Case 3: Return Value]\n");
    
    // 🧠 Call YOUR function and check the return value
    char *return_ptr = ft_strcpy(dest1, "ReturnCheck");
    
    printf("Result: \"%s\"\n", dest1);
    
    // Verification
    if (return_ptr == dest1)
        printf("✅ SUCCESS: Return value points to destination array.\n");
    else
        printf("❌ FAILURE: Return value does not point to destination.\n");

    return 0;
}
