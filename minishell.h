
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
        APPEND = 'a',
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

//START PARCING>>>>>>>>>>>>>>>>>>>>>>>>>>>>

typedef struct s_file
{
    char    *file;
    int     redir_in;
    int     redir_out;
    int     append;
    int     heredoc;
    char    *eof;
    int     index;
    struct s_file  *next;
    struct s_file  *prev;
}   t_file;


typedef struct s_parce_node
{
    char    *cmd;
    char    **args;
    t_file  *file;
    struct  s_parce_node    *next;
    struct  s_parce_node    *prev;
}   t_parce_node;



int		    lexer(char *str, t_vars *data);
char	    **split_lexer(char const *s, char *c);
int         in_delimiters(char a, char *delimiters);
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
void	    fill_output_in_node(char *str, int *i, t_vars *data);
void	    fill_string_in_node(char *str, int *i, t_vars *data, char *delimiters);
void	    fill_pipe_in_node(int *i, t_vars *data);
void	    fill_env_in_node(char *str, int *i, t_vars *data, char *delimiters);
void	    fill_white_spaces_in_node(char *str, int *i, t_vars *data);
void	    ft_malloc_lstclear(t_leaks **lst);
void	    ft_malloc_lstadd_back(t_leaks **lst, t_leaks *new);
t_leaks	    *malloc_lstnew(void *content);
void        *ft_malloc(int size, int flag);
char	    *my_strdup_two(const char *s1);

int         check_quotes(char *str);
void	    ft_my_lstdelone(Datatoken *lst);
int     	ft_parce_lstsize(Datatoken *lst);
void        ft_expand(Datatoken *lst);
Datatoken	*ft_my_lstlast(Datatoken *lst);

void            ft_parce(t_parce_node **parce, t_vars *data);
t_parce_node	*ft_parce_lstnew(void *cmd, t_file *file);
t_parce_node	*ft_parce_lstlast(t_parce_node *lst);
void	        ft_parce_lstadd_back(t_parce_node **lst, t_parce_node *new);

t_file	*ft_file_lstnew(char *file, int redir_in, int redir_out);
t_file	*ft_file_lstlast(t_file *lst);
void	ft_file_lstadd_back(t_file **lst, t_file *new);
t_file	*ft_file_heredoc_lstnew(int heredoc, char *eof, int index);
t_file	*ft_file_heredoc_lstlast(t_file *lst);
void	ft_file_heredoc_lstadd_back(t_file **lst, t_file *new);
t_file	*ft_file_append_lstnew(char *file, int append);
t_file	*ft_file_append_lstlast(t_file *lst);
void	ft_file_append_lstadd_back(t_file **lst, t_file *new);
char	**split_lexer(char const *s, char *c);


#endif
