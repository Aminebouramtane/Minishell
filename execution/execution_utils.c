#include "../minishell.h"

void	free_split(char **command_av)
{
	int	i;

	i = 0;
	while (command_av[i])
	{
		free(command_av[i]);
		i++;
	}
	free(command_av);
}

char	*error_strjoin_path(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
}

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;
	int		len;

	error_strjoin_path(s1, s2);
	i = 0;
	j = 0;
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

char	**make_env_array(t_env *env)
{
	t_env	*temp;
	char	**env_array;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	temp = env;
	while (temp)
	{
		env_array[i] = ft_strdup(temp->env_var);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_value(char *key)
{
	t_env	*temp;

	temp = envi;
	while (temp && ft_strncmp(temp->key, key) != 0)
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	else
		return (temp->value);
}
