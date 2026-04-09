
#include <stdlib.h>    //  for exit()
#include <sys/types.h> // for pid_t
#include <unistd.h>    // for fork(), pipe(), close(), dup2(), execvp()

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t	pid;

	if ((type != 'r' && type != 'w') || !file || !argv)
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
	// fork passes the child ID to the parent and 0 to the child
	// current process is the parent
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
	// current process is the child (if (pid == 0) {[...]})
	else
	{
		// 'r' means that the parent wants to read
		// --> child needs to write
		if (type == 'r')
		{
			// this redirects child stdout to write end of pipe
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(-1);
		}
		// 'w' (other possibility) means that the parent wants to write
		// --> child needs to read
		else
		{
			// this redirects child stdin to read end of pipe
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(-1);
		}
		// close up the custom streams,
		// as they have been duplicated unto STDIN/STDOUT
		close(fd[0]);
		close(fd[1]);
		// this replaces current process with process of executable from PATH-file
		execvp(file, argv);
		// execvp replaces further lines, so exit just handles a execvp failure
		exit(-1);
		// -> execvp takes over the current process and terminates afterwards
		// --> this is why execvp has to be called in its own forked process
		// it can't be done in one process,
		// since the parent process wouldn't be able to return anything
	}
}

// note: exit() forcefully closes all open FDs,
	// so manual closing is not necessary
