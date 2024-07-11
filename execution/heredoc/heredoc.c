#include "../../minishell.h"


void handel_heredoc(t_parce_node *parce)
{
    int     f;
    int     fd;
    char    *delimiter;
    char    *input = NULL;
    char    *line;
    char    *myfile;

    f = fork();
    if (f == -1)
        return ;
    else if (f == 0)
    {
        while (parce->file)
        {
            if (parce->file->heredoc == 1)
            {
                myfile = parce->file->file;
                delimiter = parce->file->eof;
                fd = open(myfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
                if (fd < 0)
                {
                    ft_putstr_fd("Error in FD !!\n", 1);
                    envi->exit_status = 1;
                    exit(1);
                }
                while (1)
                {
                    input = readline(">");
                    // output = expand_env_vars(input);
                    // if (!output)
                    //     break;
                    if (!ft_strncmp(input, delimiter))
                    {
                        free(input);
                        break;
                    }
                    if (parce->file->is_quoted)
                        line = ft_my_strjoin(input, "\n");
                    else
                        line = expande_heredoc(input);
                    write(fd, line, ft_strlen(line));
                    free(line);
                    free(input);
                }
                close(fd);
            }
            parce->file = parce->file->next;
        }
        envi->exit_status = 0;
        exit(0);
    }
    waitpid(f, NULL, 0);
}
