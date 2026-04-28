
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fd[2];
	int	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	if ((pid = fork()) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], 1) == -1)
			{
				close(fd[0]);
				close(fd[1]);
				exit(-1);
			}
		}
		else
		{
			if (dup2(fd[0], 0) == -1)
			{
				close(fd[0]);
				close(fd[1]);
				exit(-1);
			}
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(-1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return (fd[0]);
		}
		else
		{
			close(fd[0]);
			return (fd[1]);
		}
	}
	return (-1);
}
