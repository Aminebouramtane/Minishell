/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:45:01 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/09 18:40:08 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	countlength(long a)
{
	int	count;

	count = 0;
	if (a < 0)
	{
		a *= -1;
		count = 1;
	}
	while (a >= 10)
	{
		count++;
		a /= 10;
	}
	return (count + 1);
}

static char	*writeints(long a, int length, char *string)
{
	int	i;
	int	number;

	i = 0;
	if (a < 0)
	{
		string[0] = '-';
		i++;
		a *= -1;
	}
	while (length > i)
	{
		number = a % 10;
		string[length - 1] = number + '0';
		length--;
		a /= 10;
	}
	return (string);
}

char	*ft_my_itoa(int n)
{
	long	a;
	char	*itoaed;
	int		length;

	a = n;
	length = countlength(a);
	itoaed = ft_calloc(length + 1, 1);
	if (!itoaed)
		return (NULL);
	itoaed = writeints(n, length, itoaed);
	return (itoaed);
}

void	child_shlvl(char *value, t_env *temp, pid_t pid, int shlvl)
{
	if (pid == 0)
	{
		value = get_value("SHLVL");
		while (temp && ft_strncmp(temp->key, "SHLVL") != 0)
			temp = temp->next;
		if (value != NULL)
		{
			shlvl = ft_atoi(temp->value) + 1;
			if (temp && temp->value)
			{
				free(temp->value);
				temp->value = NULL;
				temp->value = ft_my_itoa(shlvl);
			}
		}
		else
		{
			if (temp && temp->value)
			{
				free(temp->value);
				temp->value = NULL;
				temp->value = ft_itoa(1);
			}
		}
	}
}

void	handle_shlvl(void)
{
	t_env	*temp;
	char	*value;
	int		shlvl;
	int		status;
	pid_t	pid;

	shlvl = 0;
	status = 0;
	value = NULL;
	temp = g_envi;
	pid = fork();
	child_shlvl(value, temp, pid, shlvl);
	signal(SIGINT, SIG_IGN);
	waiting(pid, &status);
}
