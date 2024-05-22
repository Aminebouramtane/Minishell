/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:42 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 16:00:26 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ldapsearch uid=abouramt
#include "minishell.h"

t_vars	*data;

int main(int ac, char **av)
{
    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 1);
        exit(1);
    }
    char *input;
    data = ft_malloc(sizeof(t_vars), 0);
	if (!data)
		return (0);
        data->flag = 0;
    while (1) {
        ft_my_lstclear(&data->ndata);
        input = readline("minishell>");
        if (!input[0] || !input)
            break;
        lexer(input, data);
        free(input);
    }
    ft_malloc(sizeof(t_vars), 1);
    return 0;
}
