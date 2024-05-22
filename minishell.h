/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:37:16 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 15:03:30 by abouramt         ###   ########.fr       */
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
    int         flag;
    int         f_qoute;
    Datatoken   *ndata;
} t_vars;

typedef struct s_leaks
{
    void    *add;
    struct s_leaks *next;
}   t_leaks;


int		    lexer(char *str, t_vars *data);
char	    **split_lexer(char const *s, char *c);
int         in_delimiters(char a, char *delimiters);
void	    check_quotes(char *str);
int         end_of_cmd(char *str, char *delimiter);
char	    *my_strdup(const char *s1, int size);
Datatoken	*ft_my_lstnew(void *content, char type, char state);
void	    ft_my_lstadd_back(Datatoken **lst, Datatoken *new);
void	    ft_my_lstclear(Datatoken **lst);
void	    fill_dqoute_in_node(char *str, int *i, t_vars *data);
void	    fill_qoute_in_node(char *str, int *i, t_vars *data);
void	    fill_open_in_node(int *i, t_vars *data);
void	    fill_close_in_node(int *i, t_vars *data);
void	    fill_input_in_node(char *str, int *i, t_vars *data);
void	    fill_output_in_node(int *i, t_vars *data);
void	    fill_string_in_node(char *str, int *i, t_vars *data, char *delimiters);
void	    fill_pipe_in_node(int *i, t_vars *data);
void	    fill_env_in_node(char *str, int *i, t_vars *data, char *delimiters);
void	    fill_white_spaces_in_node(char *str, int *i, t_vars *data);
void	    ft_malloc_lstclear(t_leaks **lst);
void	    ft_malloc_lstadd_back(t_leaks **lst, t_leaks *new);
t_leaks	    *malloc_lstnew(void *content);
void        *ft_malloc(int size, int flag);


#endif
