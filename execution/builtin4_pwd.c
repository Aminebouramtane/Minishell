#include "../minishell.h"

void	ft_pwd()
{
	char *path;

	path = getcwd(NULL, 0);

	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
}
