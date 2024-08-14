#include "../minishell.h"

void	successful_exit(char *cmd_path)
{
	envi->exit_status = 0;
	free(cmd_path);
	exit(0);
}

void	waiting(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		envi->exit_status = WEXITSTATUS(status);
}
