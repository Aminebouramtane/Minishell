/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:40:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/09 18:54:03 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handler_heredoc(int sigint)
{
	(void) sigint;
	ft_malloc(0, 1);
	ft_env_lstclear(g_envi);
	exit(130);
}

void	handel_heredoc(t_parce_node *parce)
{
	handle_child_process(parce);
}

static char	*read_user_input(char *delimiter)
{
	char	*input;

	signal(SIGINT, ft_handler_heredoc);
	input = readline(">");
	if (input == NULL)
	{
		printf("Minishell: warning: here-document at line \
1 delimited by end-of-file (wanted `%s')\n", delimiter);
	}
	return (input);
}

static void	process_input_line(int fd, char *input,
	char *delimiter, int is_quoted)
{
	char	*line;

	if (is_quoted)
		line = ft_my_strjoin(input, "\0");
	else
		line = expande_heredoc(input);
	write(fd, line, ft_strlen(line));
	if (ft_strncmp(input, delimiter))
		write(fd, "\n", 1);
}

void	read_and_write_heredoc(int fd, char *delimiter, int is_quoted)
{
	char	*input;

	while (1)
	{
		input = read_user_input(delimiter);
		if (input == NULL || !ft_strncmp(input, delimiter))
		{
			free(input);
			break ;
		}
		process_input_line(fd, input, delimiter, is_quoted);
		free(input);
	}
}
