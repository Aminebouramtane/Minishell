/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:37:16 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/18 10:48:03 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
    enum {
        STRING = 1,
        PIPE = '|',
        QUOTE = '\'',
        DOUBLE_COTE = '\"',
        REDIRECTION_IN = '<',
        REDIRECTION_OUT = '>',
        HERE_DOC = 2,
        VARIABLE = '$',
        OPEN_PAREN = '(',
        CLOSE_PAREN = ')'
    }           type;
    enum {
        IN_COTE,
        IN_DOUBLE_COTE,
        WITHOUT
    }           state;
    char        **args;
    char        *cmd;
    struct s_data *next;
}   Datatoken;

typedef struct s_vars
{
    char        **my_args;
    int         flag;
    Datatoken   *ndata;
} t_vars;

int		lexer(char *str);
char	**split_lexer(char const *s, char *c);

#endif
