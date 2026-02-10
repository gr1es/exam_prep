#include <stdio.h>
#include <stdlib.h>

static int	*populate_set(int argc, char *argv[])
{
	int	i;
	int	*set;

	set = malloc((argc - 2) * sizeof(int));
	if (!set)
		return (NULL);
	i = 0;
	while (i < argc - 2)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	return (set);
}

static void	solve(int target, int *set, int len, int i, int *buffer, int buff_i)
{
	int	j;

	// every number in the set was considered
	if (i == len)
	{
		if (target == 0)
		{
			j = 0;
			while (j < buff_i)
			{
				printf("%d", buffer[j]);
				j++;
				if (j != buff_i)
					printf(" ");
			}
			printf("\n");
			return ;
		}
	}
	else
	{
		// BRANCH A: INCLUDE
		buffer[buff_i] = set[i];
		solve(target - set[i], set, len, i + 1, buffer, buff_i + 1);
		// BRANCH B: EXCLUDE
		solve(target, set, len, i + 1, buffer, buff_i);
	}
}

static void	freer(int *set, int *buffer)
{
	if (set)
		free(set);
	if (buffer)
		free(buffer);
}

int	main(int argc, char *argv[])
{
	int	n;
	int	*set;
	int	*buffer;

	if (argc == 2)
		return (0);
	n = atoi(argv[1]);
	if (n == 0)
		printf("\n");
	set = populate_set(argc, argv);
	buffer = calloc(argc - 2, sizeof(int));
	if (!set || !buffer)
	{
		freer(set, buffer);
		return (1);
	}
	solve(n, set, argc - 2, 0, buffer, 0);
	freer(set, buffer);
	return (0);
}
