#include "../minishell.h"

void	execute_multi(t_parce_node *parce, char **envp)
{
	(void)parce;
	(void)envp;
	int	pid;
	int fd[2];

	while (parce != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			while (parce->file)
			{
				if (parce->file->redir_in)
					open_in_files_redir(parce);
				if (parce->file->redir_out)
					open_out_files_redir(parce);
				if (parce->file->append)
					open_files_append(parce);	
				parce->file = parce->file->next;
			}
		}
			parce = parce->next;
	}
}
