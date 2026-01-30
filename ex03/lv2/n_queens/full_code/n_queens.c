#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	*create_board(int n)
{
	int	*board;

	board = calloc(n, sizeof(int));
	if (!board)
		return (NULL);
	return (board);
}

static int	check_poss(int *board, int current_col, int target_row)
{
	int	i;
	int	ver_dist;
	int	hor_dist;

	i = 0;
	// only check prior columns!
	//.checking the first column skips this
	while (i <= current_col - 1)
	{
		if (board[i] == target_row)
			return (0);
		// get the horizontal distance
		hor_dist = current_col - i;
		// get the vertical distance
		ver_dist = board[i] - target_row;
		// vertical distance might be negative
		// if target row is below checked ro
		if (ver_dist < 0)
			ver_dist *= -1;
		// if distances are the same == vertical route
		if (hor_dist == ver_dist)
			return (0);
		i++;
	}
	return (1);
}

static void	fprintf_int(int i)
{
	fprintf(stdout, "%i", i);
}

static void	solve(int n, int *board, int current_col)
{
	int	row;

	row = 0;
	// if we made it outside the last column
	// then this solution works --> print!
	if (current_col == n)
	{
		while (row < n)
		{
			fprintf_int(board[row]);
			row++;
			if (row != n)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}
	else
	{
		while (row < n)
		{
			if (check_poss(board, current_col, row) == 1)
			{
				board[current_col] = row;
				// only if this passed the check continue with the next column
				solve(n, board, current_col + 1);
			}
			// otherwise, try the next row
			row++;
		}
	}
}

int	main(int argc, char *argv[])
{
	int	n;
	int	*board;

	if (argc != 2)
		return (0);
	n = atoi(argv[1]);
	if (n < 4 && n != 1)
	{
		fprintf(stdout, "\n");
		return (0);
	}
	board = create_board(n);
	if (!board)
		return (1);
	solve(n, board, 0);
	free(board);
	return (0);
}
