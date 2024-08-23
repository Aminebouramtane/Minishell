
#include "minishell.h"
t_env *envi;


void    ft_handler()
{
   write(1, "\n",1);
   rl_replace_line("", 0);
   rl_on_new_line();
   rl_redisplay();
}
void    ft_handler2()
{
   write(1, "\n",1);
}
void    ft_handler3()
{
    exit(0);
    write(1, "exit\n",1);
}
int main(int ac, char **av, char **env)
{
    t_vars	*data;
    char	*input;
    t_parce_node *parce;

	data = NULL;
 
    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 2);
        envi->exit_status = 1;
        exit(1);
    }
    parce = ft_malloc(sizeof(t_parce_node), 0);
    if (!parce)
        return (0);
    signal(SIGINT, ft_handler);
	envi = get_env_vars(env);
    while (1) {
        signal(SIGQUIT, SIG_IGN);
        input = readline("minishell$ ");
        if (input == NULL)
        {
            printf("exit\n");
            break;
        }
        add_history(input);
        if (!input[0] || !input)
            continue ;
		if (!check_quotes(input))
        {
			ft_putstr_fd("Error in quotes !!\n", 2);
            continue;
        }
        lexer(input, &data);
        ft_expand(data->ndata);
        if (syntax_err(data->ndata))
            continue;
        ft_parce(&parce, data);
        rem_double_quotes(&parce);
        ft_execute(parce);
        free(input);
	    ft_malloc(0 , 1);
    }
	ft_env_lstclear(envi);
    ft_malloc(0, 1);
    return 0;
}
