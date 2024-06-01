#include "../minishell.h"

int	check_builtins(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0
		|| ft_strncmp(command, "cd", 2) == 0
		|| ft_strncmp(command, "pwd", 3) == 0
		|| ft_strncmp(command, "exit", 4) == 0
		|| ft_strncmp(command, "unset", 5) == 0
		|| ft_strncmp(command, "env", 3) == 0
		|| ft_strncmp(command, "export", 6) == 0)
		return (1);
	else
		return (0);
}


void ft_execute(t_parce_node *parce)
{	
	if (parce->args && check_builtins(parce->args[0]) == 1)
		run_builtin(parce);
	// else
	// 	run_commands();
}