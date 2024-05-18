/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:42 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/18 10:20:25 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ldapsearch uid=abouramt
#include "minishell.h"

int main(int ac, char **av)
{
    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Error in Args !!\n", 1);
        exit(1);
    }
    char *input;
    int   i;

    while (1) {
        input = readline("minishell> ");
		if (!input || ft_strncmp(input, "exit", ft_strlen(input)) != 0)
			exit;
        if (lexer(input))
			return (0);
        free(input);
    }
    return 0;
}
