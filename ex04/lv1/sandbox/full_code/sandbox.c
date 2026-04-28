#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strsignal
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handler(int sig)
{
	// cast to void to prevent strict compiler unused parameter warnings
	(void)sig;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa;

	// renamed from signal to status to prevent shadowing the signal() function
	// configure the sigaction struct for the timeout logic
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	// fork in any case and handle failure
	if ((pid = fork()) == -1)
		return (-1);
	// process is child
	if (pid == 0)
	{
		// execute the requested function and exit cleanly if it finishes
		f();
		exit(0);
	}
	// process is parent
	else
	{
		// set the timer for the timeout
		alarm(timeout);
		// wait pauses the parent until the child changes state
		// waitpid returning -1 means it failed
		if (waitpid(pid, &status, 0) == -1)
		{
			// if errno is EINTR,
			// the failure was caused by our SIGALRM interruption
			if (errno == EINTR)
			{
				// kill the stuck child process
				kill(pid, SIGKILL);
				// reap the killed child to prevent a zombie process
				waitpid(pid, &status, 0);
				if (verbose == true)
					// fixed format specifier to %u for unsigned int
					printf("Bad function: timed out after %u seconds\n",
						timeout);
				return (0);
			}
		}
		// if we reach here, the child finished before the timeout
		// cancel the pending alarm
		alarm(0);
		// evaluate if the child exited normally (e.g. via exit())
		if (WIFEXITED(status))
		{
			// check if the exit code is exactly 0 (success)
			// fixed typo from WEXITsignal to standard macro WEXITSTATUS
			if (WEXITSTATUS(status) == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			// exited normally, but with an error code
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n",
						WEXITSTATUS(status));
				return (0);
			}
		}
		// evaluate if the child was terminated by a signal (e.g. segfault)
		if (WIFSIGNALED(status))
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
			return (0);
		}
		// fallback in case of an unforeseen error
		return (-1);
	}
}
