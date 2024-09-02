#include "../minishell.h"

void	successful_exit(char *cmd_path, char **envp)
{
	envi->exit_status = 0;
	if (cmd_path)
		free(cmd_path);
	ft_free(envp);
	ft_malloc(0, 1);
	exit(0);
}

void	waiting(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		envi->exit_status = WEXITSTATUS(status);
}

void	keep_in_out(void)
{
	dup2(0, 100);
	dup2(1, 99);
}

void	return_in_out(void)
{
	dup2(100, 0);
	dup2(99, 1);
}
