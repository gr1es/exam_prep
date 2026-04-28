
#include <stdbool.h>
#include <sys/types.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int signal;

	if ((pid = fork()) == -1)
		return(-1);
	if (pid == 0)
	{
		f();
		exit(0);
	}
	else
	{
		alarm(timeout);
		waitpid(pid, &signal);
	}
}
