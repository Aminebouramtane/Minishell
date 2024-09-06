/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user007 <user007@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:45:01 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 11:45:47 by user007          ###   ########.fr       */
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

void	handle_shlvl(void)
{
	t_env	*temp;
	char	*value;
	int		shlvl;
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		value = get_value("SHLVL");
		temp = g_envi;
		while (temp && ft_strncmp(temp->key, "SHLVL") != 0)
			temp = temp->next;
		if (value != NULL)
		{
			shlvl = ft_atoi(temp->value) + 1;
			temp->value = ft_my_itoa(shlvl);
		}
		else
		{
			temp->value = ft_itoa(1);
		}
	}
	waitpid(pid, &status, 0);
}
