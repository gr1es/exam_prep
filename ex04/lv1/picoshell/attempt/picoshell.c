
#include <stdlib.h>    // for exit()
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for wait()
#include <unistd.h>    // for fork(), pipe(), close(), dup2(), execvp()

int	picoshell(char **cmds[])
{
	int		prev_fd;
	int		fd[2];
	int		i;
	pid_t	pid;

	prev_fd = -1;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);
				return (1);
			}
		}
		if ((pid = fork()) == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, 0) == -1)
				{
					close(prev_fd);
					if (cmds[i + 1])
					{
						close(fd[0]);
						close(fd[1]);
					}
					exit(1);
				}
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				if (dup2(fd[1], 1) == -1)
				{
					close(fd[0]);
					close(fd[1]);
					exit(1);
				}
				close(fd[0]);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) != -1)
		;
	return (0);
}
