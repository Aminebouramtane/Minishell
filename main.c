#include "minishell.h"

t_env *envi;

void initialize_shell(int ac, char **env)
{
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 2);
        envi->exit_status = 1;
        exit(1);
    }
    signal(SIGINT, ft_handler);
    envi = get_env_vars(env);
}

char *read_main_user_input(void)
{
    char *input;

    signal(SIGQUIT, SIG_IGN);
    input = readline("minishell$ ");
    if (input == NULL)
        ft_putstr_fd("exit\n", 1);
    else
        add_history(input);
    return input;
}

int process_input(char *input, t_vars **data, t_parce_node **parce)
{
    if (!input[0] || !input)
        return 1;
    if (!check_quotes(input))
    {
        ft_putstr_fd("Error in quotes !!\n", 2);
        return 1;
    }
    lexer(input, data);
    ft_expand((*data)->ndata);
    if (syntax_err((*data)->ndata))
        return 1;
    *parce = ft_malloc(sizeof(t_parce_node), 0);
    if (!(*parce))
        return 1;
    ft_parce(parce, *data);
    rem_double_quotes(parce);
    return 0;
}

void cleanup_and_exit(void)
{
    ft_env_lstclear(envi);
    ft_malloc(0, 1);
}


int main(int ac, char **av, char **env)
{
    t_vars *data = NULL;
    char *input;
    t_parce_node *parce = NULL;

    (void)av;
    initialize_shell(ac, env);
    while (1)
    {
        input = read_main_user_input();
        if (input == NULL)
            break;
        if (process_input(input, &data, &parce))
            continue;
        ft_execute(parce, env);
        //  printf("####################PARSING#########################\n");
        //  while (parce) 
	    //  {
        //      printf("cmd ## %s\n", parce->cmd);
        //      if (parce->args)
        //      {
        //          int i = 0; 
        //          while (parce->args[i])
        //          {
        //             printf("args ## %s\n", parce->args[i]);
        //              i++;
        //          }
        //      }
        //      while (parce->file)
        //      {
        //          printf("-----------FILE : %s\n", parce->file->file);
        //          printf("-----------REDIRECTION IN : %d\n", parce->file->redir_in);
        //          printf("-----------REDIRECTION OUT : %d\n", parce->file->redir_out);
        //          printf("-----------HEREDOC : %d\n", parce->file->heredoc);
        //          printf("-----------IS_QUOTED : %d\n", parce->file->is_quoted);
        //          printf("-----------EOF : %s\n", parce->file->eof);
        //          printf("-----------INDEX : %d\n", parce->file->index);
        //          printf("======================================\n");
        //          parce->file = parce->file->next;
        //      }
        //      parce = parce->next;
        //      // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    //  }
        // printf("####################PARSING#########################\n");
        // while (parce) 
	    // {
        //     printf("cmd ## %s\n", parce->cmd);
        //     if (parce->args)
        //     {
        //         i = 0; 
        //         while (parce->args[i])
        //         {
        //            printf("args ## %s\n", parce->args[i]);
        //             i++;
        //         }
        //     }
        //     while (parce->file)
        //     {
        //         printf("-----------FILE : %s\n", parce->file->file);
        //         printf("-----------REDIRECTION IN : %d\n", parce->file->redir_in);
        //         printf("-----------REDIRECTION OUT : %d\n", parce->file->redir_out);
        //         printf("-----------HEREDOC : %d\n", parce->file->heredoc);
        //         printf("-----------IS_QUOTED : %d\n", parce->file->is_quoted);
        //         printf("-----------EOF : %s\n", parce->file->eof);
        //         printf("-----------INDEX : %d\n", parce->file->index);
        //         printf("======================================\n");
        //         parce->file = parce->file->next;
        //     }
        //     parce = parce->next;
        //     // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    // }
        free(input);
        ft_malloc(0, 1);
    }
    cleanup_and_exit();
    return 0;
}
