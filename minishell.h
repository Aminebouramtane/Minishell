/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:37:16 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/20 14:48:14 by abouramt         ###   ########.fr       */
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
        STRING = 's',
        PIPE = '|',
        QUOTE = '\'',
        DOUBLE_COTE = '\"',
        REDIRECTION_IN = '<',
        REDIRECTION_OUT = '>',
        HERE_DOC = 'h',
        VARIABLE = '$',
        OPEN_PAREN = '(',
        CLOSE_PAREN = ')',
        WHITE_SPACE = 'w'
    }           type;
    enum {
        IN_COTE ,
        IN_DOUBLE_COTE,
        GENERAL 
    }           state;
    char        *cmd;
    struct s_data *next;
    struct s_data *prev;
}   Datatoken;

typedef struct s_vars
{
    char        data_type;
    Datatoken   *ndata;
} t_vars;

int		lexer(char *str, t_vars *data);
char	**split_lexer(char const *s, char *c);
int    in_delimiters(char a, char *delimiters);
void	check_quotes(char *str);
int     end_of_cmd(char *str, char *delimiter);
char	*my_strdup(const char *s1, int size);
Datatoken	*ft_my_lstnew(void *content, char type, char state);
void	ft_my_lstadd_back(Datatoken **lst, Datatoken *new);

#endif
