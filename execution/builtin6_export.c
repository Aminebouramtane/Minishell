#include "../minishell.h"

void	show_exported(t_env	*copy)
{
	copy = copy_list(envi);
	bubblesort(copy);
	printlist(copy);
	ft_env_lstclear(copy);
}

void	append_the_export(t_parce_node *parce, t_env *temp, char *buff, int *i)
{
	while (temp && ft_strncmp(temp->key, buff) != 0)
		temp = temp->next;
	temp->env_var = ft_strdup(parce->args[i[0]]);
	temp->key = ft_substr(parce->args[i[0]], 0, i[1]);
	printf("hna 1 %s\n", get_value(buff));
	temp->value = ft_my_strjoin(get_value(buff),
			ft_my_strchr(parce->args[i[0]], '='));
	
	printf("hna 2 %s\n", ft_my_strchr(parce->args[i[0]], '='));
	printf("hna 3 %s\n", temp->value);
}

void	copy_and_sort(t_env *copy)
{
	copy = copy_list(envi);
	bubblesort(copy);
	ft_env_lstclear(copy);
}

void	process_arg(t_parce_node *parce, int *i, t_env *temp)
{
	char	*buff;

	buff = ft_strdup(parce->args[i[0]]);
	while (parce->args[i[0]][i[1]] != '\0'
		&& parce->args[i[0]][i[1]] != '='
		&& parce->args[i[0]][i[1]] != '+')
		i[1]++;
	buff[i[1]] = '\0';
	printf("========================%c\n", parce->args[i[0]][i[1]]);
	if (valid_key(buff) == 0 || (parce->args[i[0]][i[1]] == '+'
		&& valid_key(buff) == 0))
		ft_env_lstadd_back(&envi, ft_export_lstnew(parce, i[0]));
	else if (valid_key(buff) == 1 && parce->args[i[0]][i[1]] == '+')
		append_the_export(parce, temp, buff, i);
}

void	ft_export(t_parce_node *parce)
{
	t_env	*copy;
	t_env	*temp;
	int		i[2];

	copy = NULL;
	i[0] = 1;
	i[1] = 0;
	temp = envi;
	if (parce->args && parce->args[1] != NULL)
	{
		while (parce && parce->args[i[0]] != NULL)
		{
			process_arg(parce, i, temp);
			i[0]++;
			printf("i[0] = %d\n", i[0]);
			i[1] = 0;
			printf("i[1] = %d\n", i[1]);
			temp = envi;
		}
		copy_and_sort(copy);
	}
	else
	{
		printf("show_exported\n");
		show_exported(copy);
	}
}
