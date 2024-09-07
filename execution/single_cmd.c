/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:45:06 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 23:24:56 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_error(t_parce_node *temp, char **envp, char *cmd_path)
{
	if (!temp->args[0] || temp->args[0][0] == '\0')
		return ;
	if (errno == EACCES && (temp->args[0][0] == '/'
		|| temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
		|| (temp->args[0][0] == '.' && temp->args[0][1] == '/'))
		&& !access(temp->args[0], F_OK))
	{
		e_permission_denied(temp, cmd_path, envp);
	}
	else if (errno == ENOENT && (temp->args[0][0] == '/'
		|| temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
		|| (temp->args[0][0] == '.'
		&& temp->args[0][1] == '/')))
	{
		e_no_such_file(temp, cmd_path, envp);
	}
	else
		e_command_not_found(temp, cmd_path, envp);
}

void	execution_execve(char *cmd_path, t_parce_node *temp, char **envp)
{
	if (!cmd_path)
		execve_error(temp, envp, cmd_path);
	else if (execve(cmd_path, temp->args, envp) == -1)
		execve_error(temp, envp, cmd_path);
}

void	single_child(t_parce_node *temp, char *cmd_path, char **envp)
{
	open_files(temp, envp);
	cmd_path = get_cmd_path(temp);
	is_directory_check(cmd_path, envp);
	if (cmd_path && access(cmd_path, X_OK) != 0)
		check_access(cmd_path, envp);
	if (temp->args)
		execution_execve(cmd_path, temp, envp);
}

void	execute_single(t_parce_node *parce, char **envp)
{
	t_parce_node	*temp;
	int				status;
	pid_t			pid;
	char			*cmd_path;

	pid = 0;
	temp = parce;
	status = 0;
	cmd_path = NULL;
	keep_in_out();
	if (temp && temp->args && check_builtins(temp->args[0]) == 1)
		open_and_run(temp, envp);
	else if (temp && temp->args && check_builtins(temp->args[0]) != 1)
	{
		pid = fork();
		if (pid == 0)
			single_child(temp, cmd_path, envp);
		else
			waiting(pid, status);
	}
	return_in_out();
}
