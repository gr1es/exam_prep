#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Prototype for your function
int		sandbox(void (*f)(void), unsigned int timeout, bool verbose);

/* --- Test Functions --- */

void	nice_empty(void)
{
	// Does nothing, returns cleanly
}

void	nice_sleep(void)
{
	// Sleeps for 1 second, but within a 2-second timeout
	sleep(1);
}

void	bad_exit(void)
{
	// Exits with a non-zero code
	exit(42);
}

void	bad_segfault(void)
{
	int	*ptr;

	// Dereferences a NULL pointer to cause SIGSEGV
	ptr = NULL;
	*ptr = 42;
}

void	bad_abort(void)
{
	// Calls abort to cause SIGABRT
	abort();
}

void	bad_timeout(void)
{
	// Infinite loop to force the alarm to trigger
	while (1)
		;
}

/* --- Main Tester --- */

int	main(void)
{
	int	result;

	printf("=== TEST 1: Nice Function (Empty) ===\n");
	result = sandbox(nice_empty, 2, true);
	printf("Return value: %d (Expected: 1)\n\n", result);
	printf("=== TEST 2: Nice Function (Sleeps 1s, Timeout 3s) ===\n");
	result = sandbox(nice_sleep, 3, true);
	printf("Return value: %d (Expected: 1)\n\n", result);
	printf("=== TEST 3: Bad Function (Exit 42) ===\n");
	result = sandbox(bad_exit, 2, true);
	printf("Return value: %d (Expected: 0)\n\n", result);
	printf("=== TEST 4: Bad Function (Segmentation Fault) ===\n");
	result = sandbox(bad_segfault, 2, true);
	printf("Return value: %d (Expected: 0)\n\n", result);
	printf("=== TEST 5: Bad Function (Abort) ===\n");
	result = sandbox(bad_abort, 2, true);
	printf("Return value: %d (Expected: 0)\n\n", result);
	printf("=== TEST 6: Bad Function (Infinite Loop / Timeout) ===\n");
	result = sandbox(bad_timeout, 2, true);
	printf("Return value: %d (Expected: 0)\n\n", result);
	return (0);
}
