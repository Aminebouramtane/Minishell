
// ldapsearch uid=abouramt
#include "minishell.h"

t_vars	*data;

int main(int ac, char **av)
{
    char	*input;
    t_parce_node *parce;

    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 1);
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
        input = readline("minishell>");
        if (!input[0] || !input)
            break;
		if (!check_quotes(input))
		{
			ft_putstr_fd("Error in quotes !!\n", 1);
			exit(1);
		}
        lexer(input, data);
        ft_expand(data->ndata);
        ft_parce(&parce, data);
        while (data->ndata)
	    {
            printf("cmd ## %s state ## %d type ## %c\n", data->ndata->cmd, data->ndata->state, data->ndata->type);
            data->ndata = data->ndata->next;
            // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    }
        printf("#############################################\n");
        while (parce)
	    {
            printf("cmd ## %s\n", parce->cmd);
            printf("in_file ## %s\n", parce->in_file);
            printf("out_file ## %s\n", parce->out_file);
            while (parce->file)
            {
                printf("-----------FILE : %s\n", parce->file->file);
                printf("-----------REDIRECTION IN : %d\n", parce->file->redir_in);
                printf("-----------REDIRECTION OUT : %d\n", parce->file->redir_out);
                printf("======================================\n");
                parce->file = parce->file->next;
            }
            parce = parce->next;
            // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    }
        free(input);
    }
    ft_malloc(sizeof(t_vars), 1);
    return 0;
}
