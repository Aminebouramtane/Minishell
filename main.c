
// ldapsearch uid=abouramt
#include "minishell.h"

t_vars	*data;

int main(int ac, char **av)
{
    char	*input;

    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 1);
        exit(1);
    }
    data = ft_malloc(sizeof(t_vars), 0);
	if (!data)
		return (0);
    data->flag = 0;
    while (1) {
        // ft_my_lstclear(&data->ndata);
        input = readline("minishell>");
        if (!input[0] || !input)
            break;
		if (!check_quotes(input))
		{
			ft_putstr_fd("Error in quotes !!\n", 1);
			exit(1);
		}
        lexer(input, data);
        free(input);
    }
    ft_malloc(sizeof(t_vars), 1);
    return 0;
}
