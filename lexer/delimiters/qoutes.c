#include "../../minishell.h"

void process_non_special_chars(char *str, size_t *i, t_vars *data)
{
    if (!in_delimiters(str[*i], "|<>$ \t\'\""))
        fill_string_in_node(str, i, data, "|<>$ \t\'\"");
    if (str[*i] == '\'')
        fill_qoute_in_node(str, i, data);
}


void process_double_quotes(char *str, size_t *i, t_vars *data)
{
    Datatoken *node;

    if (str[*i] == '\"')
    {
        node = ft_my_lstnew("\"", '\"', IN_DOUBLE_COTE);
        ft_my_lstadd_back(&(data->ndata), node);
        if (data->f_qoute == 0)
        {
            data->f_qoute = 1;
            data->flag = 1;
        }
        else
        {
            data->flag = 0;
            return;
        }
        (*i)++;
    }
}

void process_special_chars(char *str, size_t *i, t_vars *data)
{
    if (str[*i] == '<')
        fill_input_in_node(str, i, data);
    if (str[*i] == '>')
        fill_output_in_node(str, i, data);
    if (str[*i] == '$')
        fill_env_in_node(str, i, data, "|<>$ \t\'\"");
    if (str[*i] == '|')
        fill_pipe_in_node(i, data);
    if (str[*i] == '(')
        fill_open_in_node(i, data);
    if (str[*i] == ')')
        fill_close_in_node(i, data);
    if (str[*i] == ' ' || str[*i] == '\t')
        fill_white_spaces_in_node(str, i, data);
}


void inside_dqoutes(char *str, t_vars *data)
{
    size_t i = 0;

    while (i < ft_strlen(str))
    {
        process_non_special_chars(str, &i, data);
        process_double_quotes(str, &i, data);
        process_special_chars(str, &i, data);
        if (str[i] != '\0')
            i++;
    }
}

void	fill_dqoute_in_node(char *str, size_t *i, t_vars *data)
{
	char			*tmp;
	size_t			start;
	size_t			end;

	start = *i;
	end = *i + 1;
	data->flag = 0;
	data->f_qoute = 0;
	while (str[end])
	{
		if (str[end] == '\"')
		{
			end++;
			break ;
		}
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	inside_dqoutes(tmp, data);
}
