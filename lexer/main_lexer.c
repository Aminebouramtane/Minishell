
#include "../minishell.h"

int		lexer(char *str, t_vars *data)
{
	size_t			i;

	i = 0;
	while (str[i])
	{
		if (!in_delimiters(str[i], "|<>$() \t\'\""))
		{
			fill_string_in_node(str, &i, data, "|<>$() \t\'\"");
		}
		if (str[i] == '\'')
			fill_qoute_in_node(str, &i, data);
		if (str[i] == '\"')
			fill_dqoute_in_node(str, &i, data);
		if (str[i] == '<')
			fill_input_in_node(str, &i, data);
		if (str[i] == '>')
			fill_output_in_node(str, &i, data);
		if (str[i] == '$')
			fill_env_in_node(str, &i, data, "|<>$+-/%%#@!* \t\'\"");
		if (str[i] == '|')
			fill_pipe_in_node(&i, data);
		if (str[i] == '(')
			fill_open_in_node(&i, data);
		if (str[i] == ')')
			fill_close_in_node(&i, data);
		if (str[i] == ' ' || str[i] == '\t')
			fill_white_spaces_in_node(str, &i, data);
	}
	if (data->ndata->cmd[0] == '\"')
		data->ndata = data->ndata->next;
	return(1);
}
