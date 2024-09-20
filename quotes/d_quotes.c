/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:29:44 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:34:35 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_s_quote(char *str, t_quote_state *state)
{
	if (state->inside_d_quotes)
		str[state->j++] = str[state->i];
	else if (state->inside_s_quotes)
		state->inside_s_quotes = 0;
	else
		state->inside_s_quotes = 1;
}

static void	handle_d_quote(char *str, t_quote_state *state)
{
	if (state->inside_s_quotes)
		str[state->j++] = str[state->i];
	else if (state->inside_d_quotes)
		state->inside_d_quotes = 0;
	else
		state->inside_d_quotes = 1;
}

void	process_quotes(char *str)
{
	t_quote_state	state;

	state.i = -1;
	state.j = 0;
	state.inside_d_quotes = 0;
	state.inside_s_quotes = 0;
	while (str[++state.i])
	{
		if (str[state.i] == '\'')
			handle_s_quote(str, &state);
		else if (str[state.i] == '\"')
			handle_d_quote(str, &state);
		else
			str[state.j++] = str[state.i];
	}
	str[state.j] = '\0';
}

void	rem_double_quotes(t_parce_node **node)
{
	int				i;
	t_parce_node	*data;

	data = (*node);
	while (data)
	{
		i = 0;
		while (data->args && data->args[i])
		{
			process_quotes(data->args[i]);
			i++;
		}
		data = data->next;
	}
}
