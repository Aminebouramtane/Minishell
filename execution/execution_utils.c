#include "../minishell.h"

// TO DO

/*
1st step:
************* make a fucntion that takes the env and makes an array of strings out of commands that will be executed in execve ***************
										✅ DONE !!!

2nd step:
		execute a single command using execve ✅ DONE !!

3rd step :
		a function needed to be opened files in case of redirection and append

*/

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

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return(ft_strdup(s1));
	if (!s1)
		return(ft_strdup(s2));
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

char **make_env_array(t_env *env) 
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
	{
		printf("%s\n", temp->key);
		temp = temp->next;
	}	
	if (temp == NULL)
		return (NULL);
	else
		return (temp->value);
}