/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:00:20 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/12 11:46:06 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_herdoc(t_parce_node *node)
{
	t_parce_node	*tmp;
	t_file			*file_tmp;

	tmp = node;
	while (tmp)
	{
		file_tmp = tmp->file;
		while (file_tmp)
		{
			if (file_tmp->heredoc)
				return (1);
			file_tmp = file_tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredocing(t_file *file, t_parce_node *parce, t_parce_node *tmp)
{
	t_parce_node	*node;
	pid_t			f;
	int				status;

	node = parce;
	(void)file;
	if (node)
	{
		if (check_herdoc(parce))
		{
			f = fork();
			if (f == -1)
				return (0);
			else if (f == 0)
				child_heredoc(tmp);
			waitpid(f, &status, 0);
		}
	}
	return (1);
}

void	child_heredoc(t_parce_node *tmp)
{
	while (tmp)
	{
		if (tmp->file)
		{
			handel_heredoc(tmp);
		}
		tmp = tmp->next;
	}
}
