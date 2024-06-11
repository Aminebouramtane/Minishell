#include "../minishell.h"

void	run_builtin(t_parce_node *parce)
{
	if (!parce->args)
		return ;
	if (ft_strncmp(parce->args[0], "echo") == 0)
		ft_echo(parce);
	else if (ft_strncmp(parce->args[0], "cd") == 0)
		ft_cd(parce);
	else if (ft_strncmp(parce->args[0], "unset") == 0)
		ft_unset(parce);
	 else if (ft_strncmp(parce->args[0], "env") == 0)
	 	ft_env(envi);
	else if (ft_strncmp(parce->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(parce->args[0], "export") == 0)
		ft_export(parce);
	// else if (ft_strncmp(args[0], "exit") == 0)
	// 	ft_exit(parce);
	
}


int	check_builtins(char *command)
{
	if (command && (ft_strncmp(command, "echo") == 0
		|| ft_strncmp(command, "cd") == 0
		|| ft_strncmp(command, "pwd") == 0
		|| ft_strncmp(command, "exit") == 0
		|| ft_strncmp(command, "unset") == 0
		|| ft_strncmp(command, "env") == 0
		|| ft_strncmp(command, "export") == 0))
		return (1);
	else
		return (0);
}


void ft_execute(t_parce_node *parce)
{		
	if (parce)
		handel_heredoc(parce);
	if (parce->args && check_builtins(parce->args[0]) == 1)
		run_builtin(parce);
	// else
	// 	run_commands();
}