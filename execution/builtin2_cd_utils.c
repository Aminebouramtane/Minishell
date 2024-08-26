#include "../minishell.h"

char	*ft_mystrjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	len;

	ptr = NULL;
	if (!s1 || s1 == NULL)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			ptr[i] = s1[i];
	else
		i = 0;
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

void	error_cd(char *str, int a_counter)
{
	if (a_counter == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		envi->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		envi->exit_status = 1;
	}
}

