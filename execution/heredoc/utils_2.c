/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:25:13 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/21 12:53:07 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_child_process(t_parce_node *parce)
{
	while (parce)
	{
		while (parce->file)
		{
			if (parce->file->heredoc == 1)
				process_heredoc_file(parce);
			parce->file = parce->file->next;
		}
		parce = parce->next;
	}
	g_envi->exit_status = 0;
	ft_env_lstclear(g_envi);
	ft_malloc(0, 1);
	exit(0);
}

void	process_heredoc_file(t_parce_node *parce)
{
	int		fd;
	char	*myfile;
	char	*delimiter;

	myfile = parce->file->file;
	delimiter = parce->file->eof;
	fd = open(myfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error in FD !!\n", 1);
		g_envi->exit_status = 1;
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		exit(1);
	}
	read_and_write_heredoc(fd, delimiter, parce->file->is_quoted);
	close(fd);
}

void	ft_expand_h_dolar_single_char(t_heredoc *node)
{
	if (node->input[0] == '$' && ft_strlen(node->input) == 1)
		node->input = "$";
}

void	handle_h_home_case(t_heredoc *node)
{
	char	*env;

	env = my_strdup_two(get_value("HOME"));
	if (env)
		node->input = ft_my_strjoin(env, node->input);
	else
		node->input = "\0";
}

void	handle_h_env_variable_case(t_heredoc *node, char *str)
{
	char	*env;

	env = get_value(str);
	if (env || str[0] == '?')
	{
		if (str[0] == '?')
			node->input = ft_itoa(g_envi->exit_status);
		else
			node->input = my_strdup_two(env);
	}
	else
		node->input = "\0";
}
