/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:18:35 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/26 11:48:56 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_character(char *str, size_t *i, t_vars *data)
{
	char	*sp_str;

	sp_str = "!@#$%%^&*()-=+[]{}|;:',.<>/\\\"` \t\'\"";
	if (!in_delimiters(str[*i], "|<>$() \t\'\""))
		fill_string_in_node(str, i, data, "|<>$() \t\'\"");
	if (str[*i] == '\'')
		fill_qoute_in_node(str, i, data);
	if (str[*i] == '\"')
		fill_dqoute_in_node(str, i, data);
	if (str[*i] == '<')
		fill_input_in_node(str, i, data);
	if (str[*i] == '>')
		fill_output_in_node(str, i, data);
	if (str[*i] == '$')
		fill_env_in_node(str, i, data, sp_str);
	if (str[*i] == '|')
		fill_pipe_in_node(i, data);
	if (str[*i] == '(')
		fill_open_in_node(i, data);
	if (str[*i] == ')')
		fill_close_in_node(i, data);
	if (str[*i] == ' ' || str[*i] == '\t')
		fill_white_spaces_in_node(str, i, data);
}

int	lexer(char *str, t_vars **data)
{
	size_t	i;

	i = 0;
	*data = ft_malloc(sizeof(t_vars), 0);
	if (!*data)
		return (0);
	(*data)->flag = 0;
	(*data)->f_qoute = 0;
	(*data)->ndata = NULL;
	while (str[i])
		process_character(str, &i, *data);
	return (1);
}
