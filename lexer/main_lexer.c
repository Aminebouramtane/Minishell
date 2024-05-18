/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/18 10:21:28 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_vars	*data;

int	lexer(char *str)
{
	int	i;
	int	j;
	
	i = 0;	
	data = malloc(sizeof(t_vars));
	if (!data)
		return (0);
	if (!str)
	{
		ft_putstr_fd("Error in your prompt !!", 1);
		exit(1);
	}
	data->flag = 0;
	Datatoken *token;
	token = malloc(sizeof(Datatoken));
	if (!token)
		return (0);
	token->args = split_lexer(str, " \t\n\r\f\v");
		while (token->args[i])
		{
			j = 0;
			while (token->args[i][j])
			{
				if (!ft_strchr("|><$",token->args[i][j]))
				{
					token->cmd = token->args[i];
					token->type = STRING;
					token->state = WITHOUT;
					data->flag = 1;
					data->ndata = token;
				}
				else
					printf("hiiiii");
				j++;
			}
			i++;
		}
	t_vars *curr = data;
	// printf("gdsfjhsgddf\n");
	i = 0;
	while (curr->ndata->args[i])
	{
		printf(">>>>>>>>>>%s\n", curr->ndata->args[i]);
		i++;
	}
	printf(">>>>>>>>>>%s\n", curr->ndata->cmd);
	printf(">>>>>>>>>>%d\n", curr->ndata->type);
	printf(">>>>>>>>>>%d\n", curr->flag);
	printf(">>>>>>>>>>%d\n", curr->ndata->state);
	return (1);
}

// int main(int ac, char **av)
// {
// 	lexer(av[1]);
// }

