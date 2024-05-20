/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:42 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/20 11:04:47 by abouramt         ###   ########.fr       */
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
    data = malloc(sizeof(t_vars));
	if (!data)
		return (0);

    while (1) {
        input = readline("minishell> ");
		// if (!input || ft_strncmp(input, "exit", ft_strlen(input)) != 0)
		// 	exit(0);
        lexer(input, data);
        free(input);
    }
    return 0;
}
