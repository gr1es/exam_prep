
#include <stddef.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h> // Include standard library for comparison if available

// int	main(void)
// {
// 	char	*s1;
// 	char	*accept1;
// 	char	*result1;
// 	char	*s2;
// 	char	*accept2;
// 	char	*result2;
// 	char	*s3;
// 	char	*accept3;
// 	char	*result3;
// 	char	*s4;
// 	char	*accept4;
// 	char	*result4;
// 	char	*s5;
// 	char	*accept5;
// 	char	*result5;

// 	// --- Test Case 1: Match Found at the Start ---
// 	s1 = "hello world";
// 	accept1 = "hw";
// 	result1 = ft_strpbrk(s1, accept1);
// 	printf("Test 1 (Match 'h'):\n");
// 	printf("  Input: \"%s\", Accept: \"%s\"\n", s1, accept1);
// 	printf("  Result pointer (ft_strpbrk): %s\n", result1 ? result1 : "NULL");
// 	printf("  Expected: hello world\n\n");
// 	// --- Test Case 2: Match Found in the Middle (First match is 'o') ---
// 	s2 = "programming";
// 	accept2 = "mno";
// 	result2 = ft_strpbrk(s2, accept2);
// 	printf("Test 2 (Match 'o'):\n");
// 	printf("  Input: \"%s\", Accept: \"%s\"\n", s2, accept2);
// 	printf("  Result pointer (ft_strpbrk): %s\n", result2 ? result2 : "NULL");
// 	printf("  Expected: ogramming\n\n"); // FIXED: 'o' is the first match
// 	// --- Test Case 3: No Match Found ---
// 	s3 = "c-language";
// 	accept3 = "xyz";
// 	result3 = ft_strpbrk(s3, accept3);
// 	printf("Test 3 (No Match):\n");
// 	printf("  Input: \"%s\", Accept: \"%s\"\n", s3, accept3);
// 	printf("  Result pointer (ft_strpbrk): %s\n", result3 ? result3 : "NULL");
// 	printf("  Expected: NULL\n\n");
// 	// --- Test Case 4: Empty Accept String (Edge Case) ---
// 	s4 = "test";
// 	accept4 = "";
// 	result4 = ft_strpbrk(s4, accept4);
// 	printf("Test 4 (Empty Accept):\n");
// 	printf("  Input: \"%s\", Accept: \"%s\"\n", s4, accept4);
// 	printf("  Result pointer (ft_strpbrk): %s\n", result4 ? result4 : "NULL");
// 	printf("  Expected: NULL\n\n");
// 	// --- Test Case 5: Empty Input String (Edge Case) ---
// 	s5 = "";
// 	accept5 = "abc";
// 	result5 = ft_strpbrk(s5, accept5);
// 	printf("Test 5 (Empty Input):\n");
// 	printf("  Input: \"%s\", Accept: \"%s\"\n", s5, accept5);
// 	printf("  Result pointer (ft_strpbrk): %s\n", result5 ? result5 : "NULL");
// 	printf("  Expected: NULL\n");
// 	return (0);
// }
