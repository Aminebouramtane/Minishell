/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:40:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 14:33:36 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handler_heredoc(int sigint)
{
	(void) sigint;
	exit(130);
}

void	handel_heredoc(t_parce_node *parce)
{
	int		f;
	int		status;

    f = fork();
    if (f == -1)
        return;
    else if (f == 0)
	{
        handle_child_process(parce);
		if (envi)
			ft_env_lstclear(envi);
	}
    waitpid(f, &status, 0);
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
		line = ft_my_strjoin(input, "\n");
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
