/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:47 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/14 19:15:22 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_parce_node *parce, char **envp)
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
		ft_env(envp);
	else if (ft_strncmp(parce->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(parce->args[0], "export") == 0)
		ft_export(parce, envp);
	else if (ft_strncmp(parce->args[0], "exit") == 0)
		ft_exit(parce, envp);
	else if (ft_strncmp(parce->args[0], "./minishell") == 0)
		handle_shlvl();
}

void	run_builtin1(t_parce_node *parce, char **envp, char **env)
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
		ft_env(env);
	else if (ft_strncmp(parce->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(parce->args[0], "export") == 0)
		ft_export(parce, env);
	else if (ft_strncmp(parce->args[0], "exit") == 0)
		ft_exit(parce, envp);
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

void	ft_execute(t_parce_node *parce, char **env)
{
	char			**envp;
	t_parce_node	*tmp;
	t_file			*file;

	tmp = parce;
	envp = NULL;
	file = parce->file;
	if (!heredocing(file, parce, tmp))
		return ;
	envp = make_env_array(g_envi);
	if (parce && parce->next == NULL)
		execute_single(parce, envp, env);
	else
	{
		execute_multi(parce, envp, env);
		while (waitpid(-1, NULL, 0) != -1)
		{
		}
	}
	ft_free(envp);
}
