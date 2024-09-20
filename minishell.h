/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:44:14 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/20 20:48:42 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{
	char			*env_var;
	char			*key;
	char			*value;
	int				exit_status;
	int				in_fd;
	int				out_fd;
	struct s_env	*next;
	struct s_env	*prev;

}	t_env;

extern t_env	*g_envi;

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
	}				e_type;
	enum
	{
		IN_COTE,
		IN_DOUBLE_COTE,
		GENERAL
	}				e_state;
	char			*cmd;
	struct s_data	*next;
	struct s_data	*prev;
}		t_datatoken;

typedef struct s_vars
{
	char		data_type;
	int			flag;
	int			f_qoute;
	t_datatoken	*ndata;
}		t_vars;

typedef struct s_leaks
{
	void			*add;
	struct s_leaks	*next;
}		t_leaks;

typedef struct s_file
{
	char			*file;
	int				redir_in;
	int				redir_out;
	int				append;
	int				heredoc;
	int				in_file_fd;
	int				out_file_fd;
	int				appended_file_fd;
	int				heredoc_file_fd;
	int				is_quoted;
	char			*eof;
	int				index;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_parce_node
{
	char				*cmd;
	char				*first;
	char				**args;
	t_file				*file;
	struct s_parce_node	*next;
	struct s_parce_node	*prev;
}	t_parce_node;

typedef struct s_heredoc
{
	char				*input;
	struct s_heredoc	*next;
	struct s_heredoc	*prev;
}	t_heredoc;

typedef struct s_quote_state
{
	int		i;
	int		j;
	int		inside_s_quotes;
	int		inside_d_quotes;
}	t_quote_state;

typedef struct s_special_cases
{
	t_parce_node		**parce_node;
	t_parce_node		**parce;
	t_file				**file;
	int					flag;
}	t_special_cases;

int				lexer(char *str, t_vars **data);
int				in_delimiters(char a, char *delimiters);
int				end_of_cmd(char *str, char *delimiter);
char			*my_strdup(const char *s1, int size);
t_datatoken		*ft_my_lstnew(void *content, char type, char state);
void			ft_my_lstadd_back(t_datatoken **lst, t_datatoken *new);
void			ft_my_lstclear(t_datatoken **lst);
void			fill_dqoute_in_node(char *str, size_t *i, t_vars *data);
void			fill_qoute_in_node(char *str, size_t *i, t_vars *data);
void			fill_open_in_node(size_t *i, t_vars *data);
void			fill_close_in_node(size_t *i, t_vars *data);
void			fill_input_in_node(char *str, size_t *i, t_vars *data);
void			fill_output_in_node(char *str, size_t *i, t_vars *data);
void			fill_string_in_node(char *str, size_t *i,
					t_vars *data, char *delimiters);
void			fill_pipe_in_node(size_t *i, t_vars *data);
void			fill_env_in_node(char *str, size_t *i,
					t_vars *data, char *delimiters);
void			fill_white_spaces_in_node(char *str, size_t *i, t_vars *data);
void			*ft_malloc(int size, int flag);
char			*my_strdup_two(const char *s1);
int				check_quotes(char *str);
void			ft_my_lstdelone(t_datatoken *lst);
int				ft_parce_lstsize(t_datatoken *lst);
void			ft_expand(t_datatoken *lst);
t_datatoken		*ft_my_lstlast(t_datatoken *lst);
void			ft_parce(t_parce_node **parce, t_vars *data);
t_parce_node	*ft_parce_lstnew(void *cmd, t_file *file);
t_parce_node	*ft_parce_lstlast(t_parce_node *lst);
void			ft_parce_lstadd_back(t_parce_node **lst, t_parce_node *new);
t_file			*ft_file_lstnew(char *file, int redir_in, int redir_out, int q);
t_file			*ft_file_lstlast(t_file *lst);
void			ft_file_lstadd_back(t_file **lst, t_file *new);
t_file			*ft_file_heredoc_lstnew(char *name, int is_quoted,
					char *eof, int index);
t_file			*ft_file_heredoc_lstlast(t_file *lst);
void			ft_file_heredoc_lstadd_back(t_file **lst, t_file *new);
t_file			*ft_file_append_lstnew(char *file, int append, int q);
t_file			*ft_file_append_lstlast(t_file *lst);
void			ft_file_append_lstadd_back(t_file **lst, t_file *new);
char			**split_lexer(char *s, char *delimiters);
int				syntax_err(t_datatoken *parce);
int				ft_syntax_lstsize(t_datatoken *lst);
void			rem_double_quotes(t_parce_node **node);
int				in_delimiters(char a, char *delimiters);
char			*ft_my_strjoin(char *s1, char *s2);
void			handel_heredoc(t_parce_node *parce);
void			a_permission_error(t_parce_node *temp, char *cmd_path,
					char **envp);
void			a_no_such_file(t_parce_node *temp, char *cmd_path, char **envp);
void			a_command_not_found(t_parce_node *temp, char *cmd_path,
					char **envp);
void			e_permission_denied(t_parce_node *temp,
					char *cmd_path, char **envp);
void			e_no_such_file(t_parce_node *temp,
					char *cmd_path, char **envp);
void			e_command_not_found(t_parce_node *temp,
					char *cmd_path, char **envp);
void			ft_execute(t_parce_node *parce, char **env);
void			single_child(t_parce_node *temp, char *cmd_path, char **envp);
int				alone_quotesp(t_parce_node *temp);
void			alone_quotes(t_parce_node *temp, char **envp);
void			ft_free(char **s);
int				check_builtins(char *cmd);
void			ft_echo(t_parce_node *parce);
void			into_child(int *fd);
void			back_to_parent(int *fd);
void			run_builtin1(t_parce_node *parce, char **envp, char **env);
void			run_builtin(t_parce_node *parce, char **env);
void			handle_builtins(t_parce_node *temp,
					char **envp, char *cmd_path, char **env);
void			ft_cd(t_parce_node *parce);
void			change_pwd(void);
void			pwd_ing(void);
void			update_oldpwd(t_env *oldpwd_env, char *old_pwd);
void			update_pwd(t_env *pwd_env, char *new_pwd);
char			*get_new_pwd(t_env *pwd_env);
char			*ft_mystrjoin(char *s1, char *s2);
char			*copy_ptr(char const *s1, char const *s2, char *ptr);
void			error_cd(char *str, int a_counter);
t_env			*find_env(const char *key);
void			ft_env(char **env_vars);
void			ft_pwd(void);
void			print_env(t_env *temp);
void			handle_shlvl(void);
void			ft_export(t_parce_node *parce, char **env);
int				skip_underscore(t_env	*temp);
void			ft_unset_a_node(t_env *temp);
void			ft_unset(t_parce_node *parce);
t_env			*get_env_vars(char **env_vars);
t_env			*ft_env_lstnew(void *content);
t_env			*first_env_lstnew(void *content);
void			last_com_var(t_parce_node *parce);
void			ft_env_lstadd_back(t_env **lst, t_env *new);
void			ft_env_delone(t_env *lst);
void			bubblesort(t_env *start);
void			ft_env_lstclear(t_env *head);
t_env			*ft_export_lstnew(t_parce_node *parce, int i);
void			exprt_without_value(t_env *my_node, t_parce_node *parce,
					char *buff, int *iterator);
void			append_exported(t_env *my_node, t_parce_node *parce,
					char *buff, int *iterator);
void			add_new_export(t_env *my_node, t_parce_node *parce,
					char *buff, int *iterator);
void			append_the_export(t_parce_node *parce, t_env *temp,
					char *buff, int *i);
t_env			*copy_list(t_env *start);
void			printlist(t_env *node);
void			error_exported(char *args);
int				valid_export(char *args);
void			swap_node_value(t_env *ptr1, char *temp);
void			process_arg(t_parce_node *parce, int *i, t_env *temp);
void			bubblesort(t_env *start);
int				valid_key(char *key);
void			show_exported(t_env	*copy);
void			copy_and_sort(t_env *copy);
void			*init_node(t_env	*my_node);
void			append_exported(t_env *my_node, t_parce_node *parce,
					char *buff, int *iterator);
void			add_new_export(t_env *my_node, t_parce_node *parce,
					char *buff, int *iterator);
int				ft_strncmp_env(const char *s1, const char *s2, size_t n);
void			ft_exit(t_parce_node *parce, char **envp);
void			exit_error(t_parce_node *parce, char **envp);
void			execute_single(t_parce_node *parce, char **envp, char **env);
void			execute_multi(t_parce_node *parce, char **envp, char **env);
char			**make_env_array(t_env *env);
char			*ft_strjoin_path(char const *s1, char const *s2);
int				handle_in_files(t_parce_node *temp, char **envp);
int				handle_out_files(t_parce_node *temp, char **envp);
int				handle_append_files(t_parce_node *temp, char **envp);
int				open_files_append(t_file *file, int fd_out, char **envp);
int				open_out_files_redir(t_file *parce, int fd_out, char **envp);
int				open_in_files_redir(t_file *parce, int fd_in, char **envp);
int				open_files_heredoc(t_file *file, char **envp, int fd);
void			infile_redir_child(t_parce_node *temp, int flag, char **envp);
void			ambiguous_check(int is_quote, char **envp, char *key);
int				ambiguous_check_parent(int is_quote, char *key);
int				open_files_appendp(t_file *file, int fd_out);
int				open_out_files_redirp(t_file *file, int fd_out);
int				open_in_files_redirp(t_file *file, int fd_in);
int				open_files_heredocp(t_file *file, char **envp, int fd);
void			file_error(t_file *temp, char **envp);
void			free_split(char **command_av);
void			invalid_expand(t_parce_node *temp, char **envp);
void			check_access(t_parce_node *temp, char *cmd_path, char **envp);
int				is_directory(const char *path);
int				handle_command(t_parce_node *temp, char *cmd_path, char **envp);
char			*check_dirs(char **dirs_path, int i, char *s,
					char *command_path);
char			*dirs_paths(char *env_path, t_parce_node *parce);
void			checks(t_parce_node *parce, char *cmd_path, char **envp);
void			pipe_check(int *fd);
void			fork_check(pid_t pid);
void			empty_exit(void);
void			waiting_signals(pid_t pid, int status);
void			execution_firsts(t_parce_node *temp, char **envp, int *fd,
					char **env);
void			execution_last(t_parce_node *temp, char **envp, int *fd,
					char **env);
void			keep_in_out(void);
void			return_in_out(void);
void			free_file(t_parce_node *temp, char **envp);
void			open_files_child(t_parce_node *temp, char **envp);
int				open_files_parent(t_parce_node *temp, char **envp);
void			open_and_run(t_parce_node *temp, char **envp, char **env);
char			*get_cmd_path(t_parce_node *temp, char **envp);
void			successful_exit(char *cmd_path, char **envp);
void			infile_redir_parent(t_parce_node *temp, char **envp, int flag);
char			*getpaths(t_parce_node *parce, char **envp);
void			parent_wait(pid_t pid, int status);
void			sig_handler(int sig);
void			sig_handler2(int sig);
void			waiting(pid_t pid, int *status);
void			execve_error(t_parce_node *temp, char **envp, char *cmd_path);
void			execution_execve(char *cmd_path,
					t_parce_node *temp, char **envp);
char			*get_value(char *key);
int				valid_key(char *key);
char			*ft_my_strchr(const char *s, int c);
int				max_herdoc(t_datatoken *node);
void			child_heredoc(t_parce_node *tmp);
void			open_files_heredocc(t_file *file, int fd_in);
int				heredocing(t_file *file, t_parce_node *parce,
					t_parce_node *tmp);
t_heredoc		*ft_heredoc_lstnew(void *content);
t_heredoc		*ft_heredoc_lstlast(t_heredoc *lst);
void			ft_heredoc_lstadd_back(t_heredoc **lst, t_heredoc *new);
void			ft_heredoc_lstclear(t_heredoc **lst);
void			ft_heredoc_lstdelone(t_heredoc *lst);
char			*expande_heredoc(char *str);
void			ft_heredoc_expand(t_heredoc *lst);
void			ft_expand_dolar_single_char(t_datatoken *node);
void			ft_expand_dolar_two_chars(t_datatoken *node);
void			fill_qoute_in_node(char *str, size_t *i, t_vars *data);
t_datatoken		*initialize_node(t_datatoken *data, int *len);
char			*ft_remove_qoutes(char *lst);
void			ft_remove_dqoutes(t_datatoken **lst);
void			ft_input(t_datatoken **node, t_parce_node **parce,
					t_file **file);
void			ft_append(t_datatoken **node, t_parce_node **parce,
					t_file **file);
void			ft_output(t_datatoken **node, t_parce_node **parce,
					t_file **file);
void			ft_heredoc(t_datatoken **node, t_parce_node **parce,
					t_file **file, int *flag);
void			ft_cmd(t_datatoken **node, t_parce_node **parce);
void			ft_handler(int sig);
void			ft_handler3(void);
void			child_process(t_parce_node *temp, char **envp,
					char **env, char *cmd_path);
void			preparing_child(int *fd, t_parce_node *temp, char **envp);
void			exec_com(t_parce_node *temp, char **envp, char *cmd_path);
void			handle_child_process(t_parce_node *parce);
void			process_heredoc_file(t_parce_node *parce);
void			ft_expand_h_dolar_single_char(t_heredoc *node);
void			ft_expand_h_dolar_two_chars(t_heredoc *node);
void			ft_expand_h_dolar_long(t_heredoc *node);
void			read_and_write_heredoc(int fd, char *delimiter, int is_quoted);
void			initialize_shell(int ac, char **env);
char			*read_main_user_input(void);
int				process_input(char *input, t_vars **data, t_parce_node **parce);
void			cleanup_and_exit(void);
void			process_quotes(char *str);
int				ft_count_word(char *s, char *delimiters);
void			split_quotes(char *target, char delimiter, int *index);
void			*ft_ft_calloc(size_t count, size_t size);
void			split_quotes(char *target, char delimiter, int *index);
int				skip_delimiters(char *s, char *delimiters, int i);
int				free_lstsize(t_leaks *lst);
t_leaks			*free_lstlast(t_leaks *lst);
int				ft_break(t_datatoken **node);
void			append_file(t_file **file, char *str, int a);
void			output_file(t_file **file, char *str, int a);
void			input_file(t_file **file, char *str, int a);
int				handle_final_pipe(t_datatoken *node);
void			handle_h_home_case(t_heredoc *node);
void			handle_h_env_variable_case(t_heredoc *node, char *str);
int				just_quote(t_datatoken *data);
void			ft_handle_node_types(t_datatoken **node);
void			ft_advance_node(t_datatoken **node);
int				count_quotes(t_datatoken *data, char quote_char);
int				check_for_unmatched_quotes(int quote_count, char quote_char);

#endif
