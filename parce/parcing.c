

#include "../minishell.h"
char	*ft_my_strjoin(char const *s1, char const *s2);

void    ft_input(Datatoken **node, t_parce_node **parce, t_file **file)
{
    char    *str;

    str = NULL;
    (*node) = (*node)->next;
    while (*node)
    {
        if ((*node)->type == 'w' && (*node)->state == GENERAL)
        {
            (*node) = (*node)->next;
            break;
        }
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 1, 0));
    (*parce)->in_file = str;
    (*parce)->file = *file;
}

void    ft_output(Datatoken **node, t_parce_node **parce, t_file **file)
{
    char	*str;

	str = NULL;
    (*node) = (*node)->next;
    while ((*node))
    {
        if ((*node)->type == 'w' && (*node)->state == GENERAL)
        {
            (*node) = (*node)->next;
            break;
        }
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 0, 1));
    (*parce)->out_file = str;
    (*parce)->file = *file;
}

void    ft_cmd(Datatoken **node, t_parce_node **parce)
{
    char    *str;

	str = NULL;
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<')
        || ((*node)->cmd[0] == '>' && (*node)->type == '>')
        || (*node)->type == '|' || !*node)
            break ;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
	(*parce)->cmd = str;
}

void    ft_parce(t_parce_node **parce, t_vars *data)
{
    Datatoken       *node;
	t_parce_node	*parce_node;
    t_file          *file;

    node = data->ndata;
    file = NULL;
    *parce = ft_parce_lstnew(NULL, NULL, NULL, file);
    parce_node = *parce;
    while (node)
    {
        if (node->cmd[0] == '<' && node->type == '<')
            ft_input(&node, &parce_node, &file);
        else if (node->cmd[0] == '>' && node->type == '>')
            ft_output(&node, &parce_node, &file);
        else if ((node->cmd[0] == '|' && node->type == '|'))
        {
			ft_parce_lstadd_back(parce, ft_parce_lstnew(NULL, NULL, NULL, NULL));
            file = NULL;
            parce_node = parce_node->next;
            node = node->next;
		}
        else
            ft_cmd(&node, &parce_node);
    }
}

char	*ft_my_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;
	int		len;

	i = 0;
	j = 0;
	if (!s1)
    {
        len = ft_strlen(s2);
        ptr = (char *)malloc(sizeof(char) * (len + 1));
        if (ptr == NULL)
            return (NULL);
        while (s2[j])
        {
            ptr[i + j] = s2[j];
            j++;
        }
        ptr[j] = '\0';
        return (ptr);
    }
    else 
    {
        len = ft_strlen(s1) + ft_strlen(s2);
        ptr = (char *)malloc(sizeof(char) * (len + 1));
        if (ptr == NULL)
            return (NULL);
        while (s1[i])
        {
            ptr[i] = s1[i];
            i++;
        }
        while (s2[j])
        {
            ptr[i + j] = s2[j];
            j++;
        }
        ptr[i + j] = '\0';
        return (ptr);  
    }
    return (NULL);
    
}
