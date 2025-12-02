#include <limits.h>
#include <stdio.h>

int		ft_printf(const char *format, ...);

int	main(void)
{
	int	result;

	printf("org:\n");
	result = printf("");
	printf("result org: %i\n\n\n", result);
	printf("ft:\n");
	result = ft_printf("");
	printf("result org: %i\n\n\n", result);

	// printf("org:\n");
	// result = printf("%s", NULL);
	// printf("result org: %i\n\n\n", result);
	// printf("ft:\n");
	// result = ft_printf("%s", NULL);
	// printf("result org: %i\n\n\n", result);
}
/*
void	test_str(char *s)
{
	int	r_org;
	int	r_ft;

	printf("--------------------------------------\n");
	printf("TEST: %%s with [%s]\n", s);
	printf("ORG: ");
	fflush(stdout);
	r_org = printf("%s", s);
	printf("\n");
	printf(" FT: ");
	fflush(stdout);
	r_ft = ft_printf("%s", s);
	printf("\n");
	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
	if (r_org == r_ft)
		printf("RESULT: OK\n");
	else
		printf("RESULT: FAIL\n");
	printf("\n");
}

void	test_int(int d)
{
	int	r_org;
	int	r_ft;

	printf("--------------------------------------\n");
	printf("TEST: %%d with [%d]\n", d);
	printf("ORG: ");
	fflush(stdout);
	r_org = printf("%d", d);
	printf("\n");
	printf(" FT: ");
	fflush(stdout);
	r_ft = ft_printf("%d", d);
	printf("\n");
	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
	if (r_org == r_ft)
		printf("RESULT: OK\n");
	else
		printf("RESULT: FAIL\n");
	printf("\n");
}

void	test_hex(unsigned int x)
{
	int	r_org;
	int	r_ft;

	printf("--------------------------------------\n");
	printf("TEST: %%x with [%u]\n", x);
	printf("ORG: ");
	fflush(stdout);
	r_org = printf("%x", x);
	printf("\n");
	printf(" FT: ");
	fflush(stdout);
	r_ft = ft_printf("%x", x);
	printf("\n");
	printf("RET: ORG=%d | FT=%d\n", r_org, r_ft);
	if (r_org == r_ft)
		printf("RESULT: OK\n");
	else
		printf("RESULT: FAIL\n");
	printf("\n");
}

int	main(void)
{
	// 1. STRINGS
	test_str("Hello");
	test_str("");
	test_str(NULL);
	// 2. INTEGERS
	test_int(42);
	test_int(-42);
	test_int(0);
	test_int(INT_MAX);
	test_int(INT_MIN);
	// 3. HEX
	test_hex(42);
	test_hex(0);
	test_hex(INT_MAX);
	test_hex(UINT_MAX);
	return (0);
}
*/
