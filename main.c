
// ldapsearch uid=abouramt
#include "minishell.h"
t_env *envi;
int main(int ac, char **av, char **env)
{
    t_vars	*data;
    char	*input;
    t_parce_node *parce;

	envi = get_env_vars(env);

    int     i;
    i = 0;
    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 1);
        envi->exit_status = 1;
        exit(1);
    }
    data = ft_malloc(sizeof(t_vars), 0);
	if (!data)
		return (0);
    parce = ft_malloc(sizeof(t_parce_node), 0);
    if (!parce)
        return (0);
    data->flag = 0;
    while (1) {
        // ft_my_lstclear(&data->ndata);
        data->ndata = NULL;
        input = readline("minishell$ ");
        add_history(input);
        if (!input[0] || !input)
            continue ;
		if (!check_quotes(input))
		{
			ft_putstr_fd("Error in quotes !!\n", 1);
			exit(1);
		}
        lexer(input, data);
        ft_expand(data->ndata);
        ft_parce(&parce, data);
        if (syntax_err(data->ndata))
            continue;
        rem_double_quotes(&parce);
        ft_execute(parce);
        // while (data->ndata)
	    // {
        //    printf("cmd ## %s state ## %d type ## %c\n", data->ndata->cmd, data->ndata->state, data->ndata->type);
        //     data->ndata = data->ndata->next;
        //     <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    // }
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
    }
    ft_malloc(sizeof(t_vars), 1);
    ft_malloc(sizeof(t_parce_node), 1);
    // system("leaks minishell");
    return 0;
}
