#include "../../minishell.h"

void	ft_handler_heredoc(int sigint)
{
	(void) sigint;
	exit(130);
}

void	handel_heredoc(t_parce_node *parce)
{
	int		f;
	int		fd;
	char	*delimiter;
	char	*input;
	char	*line;

	input = NULL;
	f = fork();
	if (f == -1)
		return ;
	else if (f == 0)
	{
		while (parce->file)
		{
			if (parce->file->heredoc == 1)
			{
				fd = open_files_heredoc(parce->file);
				delimiter = parce->file->eof;
				while (1)
				{
					signal(SIGINT, ft_handler_heredoc);
					input = readline(">");
					if (input == NULL)
					{
						printf("Minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", delimiter);
						break ;
					}
					if (!ft_strncmp(input, delimiter))
					{
						free(input);
						signal(SIGINT, SIG_IGN);
						break ;
					}
					if (parce->file->is_quoted)
						line = ft_my_strjoin(input, "\n");
					else
						line = expande_heredoc(input);
					write(fd, line, ft_strlen(line));
					if (ft_strncmp(input, delimiter))
						write(fd, "\n", 1);
					free(input);
				}
				close(fd);
			}
			parce->file = parce->file->next;
		}
		envi->exit_status = 0;
		ft_env_lstclear(envi);
		ft_malloc(0, 1);
		exit(0);
	}
	int status;
	waitpid(f, &status, 0);		
}
