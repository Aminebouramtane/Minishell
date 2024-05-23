/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/23 12:00:39 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	del(void *str)
{
	free(str);
}

int		lexer(char *str, t_vars *data)
{
	int			i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!in_delimiters(str[i], "|<>$() \t\'\""))
			fill_string_in_node(str, &i, data, "|<>$() \t\'\"");
		if (str[i] == '\'')
			fill_qoute_in_node(str, &i, data);
		if (str[i] == '\"')
			fill_dqoute_in_node(str, &i, data);
		if (str[i] == '<')
			fill_input_in_node(str, &i, data);
		if (str[i] == '>')
			fill_output_in_node(&i, data);
		if (str[i] == '$')
			fill_env_in_node(str, &i, data, "|<>$ \t\'\"");
		if (str[i] == '|')
			fill_pipe_in_node(&i, data);
		if (str[i] == '(')
			fill_open_in_node(&i, data);
		if (str[i] == ')')
			fill_close_in_node(&i, data);
		if (str[i] == ' ' || str[i] == '\t')
			fill_white_spaces_in_node(str, &i, data);
	}
	ft_expand_dolar(data->ndata);
	ft_expand_home(data->ndata);
	while (data->ndata)
	{
		printf("cmd ## %s\n", data->ndata->cmd);
		printf("state ## %d\n", data->ndata->state);
		printf("type ## %c\n", data->ndata->type);
		printf("========================\n");
		data->ndata = data->ndata->next;	
		// <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
	}
	return(1);
}
