/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/20 11:06:36 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



// int	lexer(char *str)
// {
// 	int	i;
// 	int	args_i;
// 	int	start;
// 	int	j;
// 	char *cmd;

// 	i = 0;
// 	args_i = 0;
// 	data = malloc(sizeof(t_vars));
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i] && in_delimiters(str[i], " \t"))
// 			i++;
// 		if (in_delimiters(str[i], "<>|"))
// 		{
// 			while (str[i] && in_delimiters(str[i], " \t"))
// 				i++;
// 			while (str[i] && !in_delimiters(str[i], "<>| \t"))
// 				i++;
// 		}
// 		if (!in_delimiters(str[i], "<>|"))
// 		{
// 			start = i;
// 			i = end_of_cmd(str + i, "<>|");
// 			cmd = my_strdup(str + start, (i - start));
// 			data->my_args = split_lexer(cmd, " \t");
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (data->my_args[i])
// 	{
		
// 		printf("%s\n", data->my_args[i]);
// 		i++;
// 	}
// 	return (1);
// }

void	*fill_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	node = malloc(sizeof(Datatoken));
	if (!node)
		return (NULL);
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"'
		|| in_delimiters(str[end], "|<> \t"))
			break;
		end++;
	}
	tmp = my_strdup(str, end);
	node = ft_my_lstnew(tmp);
	ft_my_lstadd_back(&(data->ndata), node);
}

int		lexer(char *str, t_vars *data)
{
	int			i;

	i = 0;

	if (!in_delimiters(str[i], "|<> \t"))
	{
		fill_node(str, &i, data);
	}

	printf("%s\n", data->ndata->cmd);
	printf("%c\n", data->ndata->type);
	printf("%d\n", data->ndata->state);
	return(1);
}
