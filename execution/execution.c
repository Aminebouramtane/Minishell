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
	else if (ft_strncmp(parce->args[0], "exit") == 0)
		ft_exit(parce);
	else if (ft_strncmp(parce->args[0], "./minishell") == 0)
		handle_shlvl();
}

int	check_builtins(char *command)
{
	if ((command) && (ft_strncmp(command, "echo") == 0
			|| ft_strncmp(command, "cd") == 0
			|| ft_strncmp(command, "pwd") == 0
			|| ft_strncmp(command, "exit") == 0
			|| ft_strncmp(command, "unset") == 0
			|| ft_strncmp(command, "env") == 0
			|| ft_strncmp(command, "export") == 0
			|| ft_strncmp(command, "./minishell") == 0))
		return (1);
	else
		return (0);
}

void	ft_execute(t_parce_node *parce)
{
	char	**envp;
	t_file	*file;

	envp = NULL;
	file = parce->file;
	while (file)
	{
		if (file->heredoc && file->index == 16)
		{
			printf("minishell: maximum here-document count exceeded");
			exit(2);
		}
		file = file->next;
	}
	
	if (parce)
	{
		if (parce->file)
			handel_heredoc(parce);
	}
	envp = make_env_array(envi);
	if (parce->next == NULL)
	{
		execute_single(parce, envp);
	}
	else
	{
		execute_multi(parce, envp);
		while (waitpid(-1, NULL, 0) != -1)
		{
		}
	}
}
