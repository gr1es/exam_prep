
#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fd[2];
	int	pid;

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	// pid = "process ID"; helps differenciate between parent and child
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	// current process is the parent
	// fork passes the child ID to the parent and 0 to the child
	if (pid != 0)
	{
		// parent wants to read
		if (type == 'r')
		{
			// close write end, not needed
			close(fd[1]);
			return (fd[0]);
		}
		// parent wants to write
		else
		{
			// close read end, not needed
			close(fd[0]);
			return (fd[1]);
		}
	}
	// current process is the child
	else
	{
		// 'r' means that the parent wants to read
		// --> child needs to write
		if (type == 'r')
		{
			// close read end of pipe (not used by child)
			close(fd[0]);
			// this redirects child stdout to write end of pipe
			dup2(fd[1], 1);
			// stdout is already pointing to fd of fd[1], so it can be closed
			close(fd[1]);
		}
		// 'w' (other possibility) means that the parent wants to write
		// --> child needs to read
		else
		{
			// close write end of pipe (not used by child)
			close(fd[1]);
			// this redirects child stdin to read end of pipe
			dup2(fd[0], 0);
			// stdin is already pointing to fd of fd[0], so it can be closed
			close(fd[0]);
		}
		// this replaces current process with process of executable from PATH-file
		execvp(file, argv);
		// execvp replaces further lines, so exit just handles a execvp failure
		exit(1);
	}
}
