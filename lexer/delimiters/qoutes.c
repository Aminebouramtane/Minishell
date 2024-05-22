/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:39:22 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 15:20:03 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void		inside_dquotes(char *str, t_vars *data)
{
	int			i;

	i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		printf("dfdsfsdfsdfsd\n");
		if (!in_delimiters(str[i], "|<>$ \t\'\""))
			fill_string_in_node(str, &i, data, "|<>$ \t\'\"");
		if (str[i] == '\'')
			fill_qoute_in_node(str, &i, data);
		if (str[i] == '\"')
		{
			data->ndata = ft_my_lstnew("\"", '\"', IN_DOUBLE_COTE);
			ft_my_lstadd_back(&(data->ndata), data->ndata);
			i++;
		}
		if (str[i] == '<')
			fill_input_in_node(&i, data);
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
		if (in_delimiters(str[i], " \t"))
			fill_white_spaces_in_node(str, &i, data, " \t");
	}
}

void	fill_dqoute_in_node(char *str, int *i, t_vars *data)
{
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (str[end] == '\"')
		{
			end++;
			break;
		}
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	inside_dquotes(tmp, data);
}

void	fill_qoute_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	node = ft_my_lstnew("'", '\'', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	start = *i + 1;
	end = *i + 1;
	while (str[end])
	{
		if (str[end] == '\'')
			break;
		end++;
	}
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 's', IN_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
	node = ft_my_lstnew("'", '\'', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = end + 1;
}