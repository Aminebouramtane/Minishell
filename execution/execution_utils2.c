#include "../minishell.h"

void	successful_exit(void)
{
	envi->exit_status = 0;
	exit(0);
}

void	waiting(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		envi->exit_status = WEXITSTATUS(status);
}
