/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:29:44 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 12:07:24 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parse_value(char *env)
{
	int				i;
	char			*tmp[2];
	static char		np[2] = {1, 0};

	i = 0;
	while (env && env[i])
	{
		if (env[i] == '\'' || env[i] == '\"')
		{
			tmp[0] = ft_my_substr(env, 0, i);
			tmp[1] = ft_my_strjoin(tmp[0], np);
			tmp[0] = ft_my_strjoin(tmp[1], env + i);
			env = tmp[0];
			i++;
		}
		i++;
	}
	return (env);
}

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
	while (str && str[++state.i])
	{
		if ((str[state.i] && str[state.i] == '\'' && state.i == 0)
			|| ((str[state.i] && str[state.i] == '\'')
				&& (str[state.i - 1] && str[state.i - 1] != 1)))
			handle_s_quote(str, &state);
		else if ((str[state.i] && str[state.i] == '\"' && state.i == 0)
			|| ((str[state.i] && str[state.i] == '\"')
				&& (str[state.i - 1] && str[state.i - 1] != 1)))
			handle_d_quote(str, &state);
		else
		{
			str[state.j++] = str[state.i];
			if (state.j && str[state.j - 1] && str[state.j - 1] == 1)
				state.j--;
		}
	}
	if (str && str[state.j])
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
