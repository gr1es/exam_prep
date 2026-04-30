#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 1. FORWARD DECLARATION
// We must declare level_1 here because level_3 needs to call it
static int level_1(char *str, int *i);

// 2. CENTRALIZED ERROR HANDLING
// This catches all invalid inputs and immediately kills the program.
static void error_out(char c)
{
	// we hit the null terminator unexpectedly (e.g., the string was "2+"), 
	if (c == '\0')
		printf("Unexpected end of input\n");
	// Otherwise, print the specific bad character we found (e.g., "2+a")
	else
		printf("Unexpected token '%c'\n", c);
	// The subject requires exiting with code 1 on errors
	exit(1);
}

// 3. LEVEL 3: FACTORS (Highest Priority)
// Factors are the absolute base units: raw numbers (0-9) or fully evaluated parentheses.
static int level_3(char *str, int *i)
{
	int res;

	// Case A: We found an opening parenthesis
	if (str[*i] == '(')
	{
		(*i)++; // Advance the index to move past the '(' character
		// Recursively call Level 1 to solve the entire mini-equation inside the brackets.
		// This works because level_1 obeys the order of operations naturally.
		res = level_1(str, i);
		// After solving the inside, the very next character MUST be a closing bracket
		if (str[*i] == ')')
			(*i)++; // Advance the index to move past the ')' character
		else
			error_out(str[*i]); // If it is not a ')', the user messed up the brackets
		return (res);
	}
	// Case B: We found a digit (0-9)
	else if (isdigit(str[*i]))
	{
		// Characters '0'-'9' have ASCII values 48-57. 
		// Subtracting '0' (48) converts the character into its actual mathematical integer value.
		res = str[*i] - '0';
		(*i)++; // Advance the index past the digit so the next function does not read it again
		return (res);
	}
	// Case C: We found something that isn't a number or a parenthesis (like a letter or stray operator)
	else
		error_out(str[*i]);
	return (0); // Unreachable, but prevents compiler warnings regarding return values
}

// 4. LEVEL 2: TERMS (Multiplication)
// Terms bind tighter than expressions. We must do all multiplications before additions.
static int level_2(char *str, int *i)
{
	// First, get the left side of the multiplication
	int res = level_3(str, i);

	// A while loop is used instead of an 'if' statement to allow for 
	// chained multiplications like "2 * 3 * 4". It keeps eating '*' symbols until none are left.
	while (str[*i] == '*')
	{
		(*i)++; // Advance the index past the '*' operator
		// Get the next factor on the right, and multiply it against our running total
		res *= level_3(str, i);
	}
	return (res);
}

// 5. LEVEL 1: EXPRESSIONS (Addition)
// Expressions are the lowest priority. We only add AFTER terms (multiplications) are solved.
static int level_1(char *str, int *i)
{
	// First, get the left side of the addition.
	// By calling level_2 here, we guarantee that any pending multiplications 
	// are fully resolved before we even look for a '+' sign.
	int res = level_2(str, i);

	// A while loop is used to allow for chained additions like "2 + 3 + 4"
	while (str[*i] == '+')
	{
		(*i)++; // Advance the index past the '+' operator
		// Get the next resolved term on the right, and add it to our running total
		res += level_2(str, i);
	}
	return (res);
}

// 6. MAIN ENTRY POINT
int main(int argc, char **argv)
{
	// The program only accepts exactly one string argument
	if (argc != 2)
		return (0);

	char *str = argv[1];
		
	// We create an index variable to track our global position in the string.
	int i = 0; 

	// We pass the ADDRESS of 'i' (&i) into the parser.
	// This is critical. Because we pass it by reference, when a deeper function 
	// like level_3 does (*i)++, the change happens to this exact variable in main, 
	// permanently advancing the reading position for every function.
	int res = level_1(str, &i);

	// Crucial Check: If the parser finished its job, but our index 'i' has not reached
	// the '\0' null terminator, it means there is garbage at the end of the string (e.g., "2+2xyz").
	if (str[i] != '\0')
		error_out(str[i]);
	// If everything succeeded and the string is fully consumed, print the final mathematical result.
	printf("%d\n", res);
	return (0);
}
