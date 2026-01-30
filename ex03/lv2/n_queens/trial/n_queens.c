
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	*create_board(int n)
{
	int	*board;

	board = calloc(sizeof(int), n);
	if (!board)
		return (NULL);
	return (board);
}

static int	check(int *board, int current_col, int target_row)
{
	int	i;
	int	hor_dist;
	int	ver_dist;

	i = 0;
	while (i < current_col)
	{
		// vertical row check
		if (board[i] == target_row)
			return (0);
		// diagonal check:
		// horizontal distance == vertical distance?
		hor_dist = current_col - i;
		ver_dist = target_row - board[i];
		if (ver_dist < 0)
			ver_dist *= -1;
		if (hor_dist == ver_dist)
			return (0);
		i++;
	}
	return (1);
}

static void	solve(int n, int *board, int current_col)
{
	int	row;

	row = 0;
	// we escaped the last row
	// --> solution found!
	if (current_col == n)
	{
		while (row < n)
		{
			fprintf(stdout, "%i", board[row]);
			row++;
			if (row != n)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
		return ;
	}
	while (row < n)
	{
		if (check(board, current_col, row) == 1)
		{
			board[current_col] = row;
			solve(n, board, current_col + 1);
		}
		row++;
	}
}

int main (int argc, char *argv[])
{
	int n;
	int *board;

	if (argc != 2)
		return (1);
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
