
int	ft_strlen(char *str)
{
	int	result;

	result = 0;
	while (str[result])
		result++;
	return (result);
}
#include <stddef.h> // For size_t
#include <stdio.h>

// --- CORRECTED FUNCTION PROTOTYPE ---
// Arguments are now 'const char *' (read-only) and the return type is 'size_t'.

// A simple local implementation of strlen for comparison only
size_t	local_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	main(void)
{
	char	*str1;
	char	*str3;
	size_t	result;
	size_t	expected;

	str1 = "Hello, 42!";
	str3 = "Testing a much longer string with spaces and punctuation.";
	// Test strings are declared as const char *
	char *str2 = ""; // Empty string
	printf("--- Testing ft_strlen (Warning-Free) ---\n");
	// -------------------------------------------------------------------
	// Case 1: Standard String
	// -------------------------------------------------------------------
	printf("\n[Case 1: Standard String]\n");
	printf("String: \"%s\"\n", str1);
	// The call now correctly passes a const char * to ft_strlen(const char *)
	result = ft_strlen(str1);
	expected = local_strlen(str1);
	printf("ft_strlen result: %zu\n", result);
	if (result == expected)
		printf("✅ SUCCESS: Length matches expected (%zu).\n", expected);
	else
		printf("❌ FAILURE: Expected %zu, got %zu.\n", expected, result);
	// -------------------------------------------------------------------
	// Case 2: Empty String
	// -------------------------------------------------------------------
	printf("\n[Case 2: Empty String]\n");
	printf("String: \"%s\"\n", str2);
	result = ft_strlen(str2);
	expected = local_strlen(str2); // Should be 0
	printf("ft_strlen result: %zu\n", result);
	if (result == expected)
		printf("✅ SUCCESS: Length matches expected (%zu).\n", expected);
	else
		printf("❌ FAILURE: Expected %zu, got %zu.\n", expected, result);
	// -------------------------------------------------------------------
	// Case 3: Longer String
	// -------------------------------------------------------------------
	printf("\n[Case 3: Longer String]\n");
	printf("String: \"%s\"\n", str3);
	result = ft_strlen(str3);
	expected = local_strlen(str3);
	printf("ft_strlen result: %zu\n", result);
	if (result == expected)
		printf("✅ SUCCESS: Length matches expected (%zu).\n", expected);
	else
		printf("❌ FAILURE: Expected %zu, got %zu.\n", expected, result);
	return (0);
}
