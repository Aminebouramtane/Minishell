/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/20 18:47:16 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_string_in_node(char *str, int *i, t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	while (str[end])
	{
		if (in_delimiters(str[end], delimiters))
			break;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 's', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// free(tmp);
	// tmp = NULL;
	// ft_my_lstclear(&node, del);
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
	// free(tmp);
	// tmp = NULL;
	// ft_my_lstclear(&node, del);
	*i = end + 1;
}

void	fill_input_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("<", '<', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_env_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("$", '$', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_output_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew(">", '>', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_pipe_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("|", '|', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_open_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("(", '(', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_close_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew(")", ')', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// ft_my_lstclear(&node, del);
	*i = *i + 1;
}

void	fill_dqoute_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	node = ft_my_lstnew("\"", '\"', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	start = *i + 1;
	end = *i + 1;
	while (str[end])
	{
		if (str[end] == '\"')
			break;
		end++;
	}
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
	node = ft_my_lstnew("\"", '\"', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// free(tmp);
	// tmp = NULL;
	// ft_my_lstclear(&node, del);
	*i = end + 1;
}

void	fill_white_spaces_in_node(char *str, int *i, t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	while (str[end])
	{
		if (!in_delimiters(str[end], delimiters))
			break;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 'w', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	// free(tmp);
	// tmp = NULL;
	// ft_my_lstclear(&node, del);
}

void	del(void *str)
{
	free(str);
}

int		lexer(char *str, t_vars *data)
{
	int			i;

	i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		if (!in_delimiters(str[i], "|<> \t\'\""))
			fill_string_in_node(str, &i, data, "|<>$ \t\'\"");
		if (str[i] == '\'')
			fill_qoute_in_node(str, &i, data);
		if (str[i] == '\"')
			fill_dqoute_in_node(str, &i, data);
		if (str[i] == '<')
			fill_input_in_node(&i, data);
		if (str[i] == '>')
			fill_output_in_node(&i, data);
		if (str[i] == '$')
			fill_env_in_node(&i, data);
		if (str[i] == '|')
			fill_pipe_in_node(&i, data);
		if (str[i] == '(')
			fill_open_in_node(&i, data);
		if (str[i] == ')')
			fill_close_in_node(&i, data);
		else if (in_delimiters(str[i], " \t\v\n\r\f"))
			fill_white_spaces_in_node(str, &i, data, " \t\v\n\r\f");
	}
	while (data->ndata)
	{
		printf("cmd >>>%s\n", data->ndata->cmd);
		printf("state >>>%d\n", data->ndata->state);
		printf("type >>>%c\n", data->ndata->type);
		printf("========================\n");
		data->ndata = data->ndata->next;	
	}
	return(1);
}
