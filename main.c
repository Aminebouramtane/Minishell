/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:56:25 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 14:02:51 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_envi;

void	initialize_shell(int ac, char **env)
{
	if (ac != 1)
	{
		ft_putstr_fd("Error in Args !!\n", 2);
		exit(1);
	}
	g_envi = get_env_vars(env);
}

char	*read_main_user_input(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handler);
	input = readline("minishell$ ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
	}
	else if (*input != '\0')
		add_history(input);
	return (input);
}

int	process_input(char *input, t_vars **data, t_parce_node **parce)
{
	if (!input[0] || !input)
		return (1);
	if (!check_quotes(input))
	{
		ft_putstr_fd("Error in quotes !!\n", 2);
		return (1);
	}
	lexer(input, data);
	ft_expand((*data)->ndata);
	if ((*data)->ndata && max_herdoc((*data)->ndata))
	{
		ft_putstr_fd("Minishell: maximum here-document count exceeded\n", 2);
		return (1);
	}
	if ((*data)->ndata && syntax_err((*data)->ndata))
		return (1);
	*parce = ft_malloc(sizeof(t_parce_node), 0);
	if (!(*parce))
		return (1);
	ft_parce(parce, *data);
	rem_double_quotes(parce);
	return (0);
}

void	cleanup_and_exit(void)
{
	ft_env_lstclear(g_envi);
	ft_malloc(0, 1);
}

int	main(int ac, char **av, char **env)
{
	t_vars			*data;
	char			*input;
	t_parce_node	*parce;

	(void)av;
	data = NULL;
	parce = NULL;
	initialize_shell(ac, env);
	while (1)
	{
		input = read_main_user_input();
		if (input == NULL)
			break ;
		if (process_input(input, &data, &parce))
			continue ;
		last_com_var(parce);
		ft_execute(parce, env);
	    // printf("####################PARSING#########################\n");
        // while (parce) 
	    // {
        //     // printf("cmd ## %s\n", parce->cmd);
        //     if (parce->args)
        //     {
        //         int i = 0; 
        //         while (parce->args[i])
        //         {
        //            printf("args ## %s\n", parce->args[i]);
        //             i++;
        //         }
        //     }
        //     while (parce->file)
        //     {
        //         // printf("-----------FILE : %s\n", parce->file->file);
        //         // printf("-----------REDIRECTION IN : %d\n", parce->file->redir_in);
        //         // printf("-----------REDIRECTION OUT : %d\n", parce->file->redir_out);
        //         // printf("-----------HEREDOC : %d\n", parce->file->heredoc);
        //         // printf("-----------IS_QUOTED : %d\n", parce->file->is_quoted);
        //         // printf("-----------EOF : %s\n", parce->file->eof);
        //         // printf("-----------INDEX : %d\n", parce->file->index);
        //         // printf("======================================\n");
        //         parce->file = parce->file->next;
        //     }
        //     parce = parce->next;
        //     // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	    // }
		free(input);
		ft_malloc(0, 1);
	}
	cleanup_and_exit();
	return (0);
}
