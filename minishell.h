
#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_env
{
    char *env_var;

	char	*key;
	char	*value;
	struct s_env *next;
	struct s_env *prev;

}   t_env;
extern t_env *envi;
typedef struct s_data
{
	enum
	{
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
	}		type;
	enum
	{
		IN_COTE,
		IN_DOUBLE_COTE,
		GENERAL
	}		state;
	char			*cmd;
	struct s_data	*next;
	struct s_data	*prev;
}		Datatoken;

typedef struct s_vars
{
	char		data_type;
	int			flag;
	int			f_qoute;
    Datatoken	*ndata;
}		t_vars;

typedef struct s_leaks
{
	void			*add;
	struct s_leaks	*next;
}		t_leaks;

//START PARCING>>>>>>>>>>>>>>>>>>>>>>>>>>>>

typedef struct s_file
{
    char    *file;
    int     redir_in;
    int     redir_out;
    int     append;
    int     heredoc;
	int		is_quoted;
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



int				lexer(char *str, t_vars *data);
int				in_delimiters(char a, char *delimiters);
int				end_of_cmd(char *str, char *delimiter);
char			*my_strdup(const char *s1, int size);
Datatoken		*ft_my_lstnew(void *content, char type, char state);
void	    	ft_my_lstadd_back(Datatoken **lst, Datatoken *new);
void			ft_my_lstclear(Datatoken **lst);
void			fill_dqoute_in_node(char *str, size_t *i, t_vars *data);
void			fill_qoute_in_node(char *str, size_t *i, t_vars *data);
void			fill_open_in_node(size_t *i, t_vars *data);
void			fill_close_in_node(size_t *i, t_vars *data);
void			fill_input_in_node(char *str, size_t *i, t_vars *data);
void			fill_output_in_node(char *str, size_t *i, t_vars *data);
void			fill_string_in_node(char *str, size_t *i, t_vars *data, char *delimiters);
void			fill_pipe_in_node(size_t *i, t_vars *data);
void			fill_env_in_node(char *str, size_t *i, t_vars *data, char *delimiters);
void			fill_white_spaces_in_node(char *str, size_t *i, t_vars *data);
void			ft_malloc_lstclear(t_leaks **lst);
void			ft_malloc_lstadd_back(t_leaks **lst, t_leaks *new);
t_leaks			*malloc_lstnew(void *content);
void			*ft_malloc(int size, int flag);
char			*my_strdup_two(const char *s1);

int				check_quotes(char *str);
void			ft_my_lstdelone(Datatoken *lst);
int				ft_parce_lstsize(Datatoken *lst);
void			ft_expand(Datatoken *lst);
Datatoken		*ft_my_lstlast(Datatoken *lst);

void			ft_parce(t_parce_node **parce, t_vars *data);
t_parce_node	*ft_parce_lstnew(void *cmd, t_file *file);
t_parce_node	*ft_parce_lstlast(t_parce_node *lst);
void			ft_parce_lstadd_back(t_parce_node **lst, t_parce_node *new);

t_file			*ft_file_lstnew(char *file, int redir_in, int redir_out);
t_file			*ft_file_lstlast(t_file *lst);
void			ft_file_lstadd_back(t_file **lst, t_file *new);
t_file			*ft_file_heredoc_lstnew(char *name, int is_quoted, char *eof, int index);
t_file			*ft_file_heredoc_lstlast(t_file *lst);
void			ft_file_heredoc_lstadd_back(t_file **lst, t_file *new);
t_file			*ft_file_append_lstnew(char *file, int append);
t_file			*ft_file_append_lstlast(t_file *lst);
void			ft_file_append_lstadd_back(t_file **lst, t_file *new);
char			**split_lexer(char *s, char *delimiters);
int				syntax_err(Datatoken *parce);
int				ft_syntax_lstsize(Datatoken *lst);
void			rem_double_quotes(t_parce_node **node);
int				in_delimiters(char a, char *delimiters);
void			skip_quotes(char *target, char delimiter, int *index);
char			*ft_my_strjoin(char *s1, char *s2);
void    		handel_heredoc(t_parce_node *parce);
char			*expand_env_vars(const char *input);
int				ft_here_isalnum(int c);
size_t			ft_here_strlen(const char *s);
char			*ft_here_strncat(char *dest, const char *src, size_t n);
char			*ft_here_strncpy(char *dest, const char *src, size_t n);
char			*ft_here_strchr(const char *s, int c);
char			*ft_here_strcat(char *dest, const char *src);
//-=----------------------------------execution_prototypes--------------------------------------//


void	ft_free(char **s);
int     check_builtins(char *cmd);
void	ft_echo(t_parce_node *parce);
void    ft_execute(t_parce_node *parce);
void	run_builtin(t_parce_node *parce);
void    ft_cd(t_parce_node *parce);
void    ft_env();
void    ft_pwd();
void	ft_export(t_parce_node *parce);
void	ft_unset(t_parce_node *parce);
t_env	*get_env_vars(char **env_vars);

t_env	*ft_env_lstnew(void *content);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
void	ft_env_delone(t_env *lst);
void	bubbleSort(t_env *start);
void	ft_env_lstclear(t_env *head);
t_env	*ft_export_lstnew(t_parce_node *parce, int i);

#endif
