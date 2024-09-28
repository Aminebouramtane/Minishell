/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:45:06 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/27 15:46:54 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_error(t_parce_node *temp, char **envp, char *cmd_path)
{
	if (temp && temp->args && (!temp->args[0] || temp->args[0][0] == '\0'))
		return ;
	if (errno == EACCES && temp && temp->args && (temp->args[0][0] == '/'
		|| temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
		|| (temp->args[0][0] == '.' && temp->args[0][1] == '/'))
		&& !access(temp->args[0], F_OK))
	{
		e_permission_denied(temp, cmd_path, envp);
	}
	else if (errno == ENOENT && temp && temp->args && (temp->args[0][0] == '/'
		|| temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
		|| (temp->args[0][0] == '.'
		&& temp->args[0][1] == '/')
		|| (temp->args[0][0] == '.'
		&& (temp->args[0][1] == '.')
		&& (temp->args[0][2] == '/'))))
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

void	parent_wait(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	waiting(pid, &status);
}

void	single_child(t_parce_node *temp, char *cmd_path, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	open_files_child(temp, envp);
	cmd_path = get_cmd_path(temp, envp);
	handle_command(temp, cmd_path, envp);
	if (cmd_path && access(cmd_path, X_OK) != 0)
		check_access(temp, cmd_path, envp);
	if (temp->args)
		execution_execve(cmd_path, temp, envp);
}

void	execute_single(t_parce_node *parce, char **envp, char **env)
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
	if (temp && temp->file && !temp->args)
		open_files_parent(temp, envp);
	if (alone_quotesp(temp))
		return ;
	if (temp && temp->args && check_builtins(temp->args[0]) == 1)
		open_and_run(temp, envp, env);
	else if (temp && temp->args && check_builtins(temp->args[0]) != 1)
	{
		pid = fork();
		if (pid == 0)
			single_child(temp, cmd_path, envp);
		else
			parent_wait(pid, status);
	}
	return_in_out();
}
