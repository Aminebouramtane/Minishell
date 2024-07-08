#include "../minishell.h"

void	execute_multi(t_parce_node *parce, char **envp)
{
	(void)parce;
	(void)envp;
	int	pid;

	pid = 0;
	while (parce != NULL)
	{
		pid = fork();
		parce = parce->next;
	}
	
}
