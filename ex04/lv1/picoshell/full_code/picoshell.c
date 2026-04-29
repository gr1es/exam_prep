#include <stdlib.h>    // for exit()
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for wait
#include <unistd.h>    // for NULL, pipe, fork, dup2, execvp, close

int	picoshell(char **cmds[])
{
	int		prev_fd;
	int		fd[2];
	pid_t	pid;
	int		i;

	prev_fd = -1;
	i = 0;
	// loop through every command (= every array of strings)
	while (cmds[i])
	{
		// if there is a following command ...
		if (cmds[i + 1])
		{
			// ... open a new pipe
			if (pipe(fd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);
				return (1);
			}
		}
		// fork in any case
		if ((pid = fork()) == -1)
		{
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			// clean up fd if this is not the first process
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		// process is child
		if (pid == 0)
		{
			// if there was a prior process
			if (prev_fd != -1)
			{
				// -> take previous fd as STDIN
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
				// close write from prior process
				close(prev_fd);
				// in case of pev_fd == -1, it does not need to be closed
			}
			// if there is another command coming up ...
			if (cmds[i + 1])
			{
				// ... send this process' output to pipe instead of STDOUT (terminal)
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
		// process is parent
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
	// wait pauses the process until any of its children terminates
	// no children --> wait returns -1
	// argument = pointer to error code index (not used here)
	while (wait(NULL) != -1)
		;
	return (0);
}
