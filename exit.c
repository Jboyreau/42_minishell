/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 04:22:20 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 16:06:14 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	signe;
	int	nb;

	signe = 1;
	nb = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signe *= -signe;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		nb = 10 * nb + (*nptr - 48);
		nptr++;
	}
	return (nb * signe);
}

int	ft_exit(t_leaf *cmd, t_exec *ex, int *tempfd)
{
	int	code;

	if ((cmd->arg[1]) == 0)
		code = 0;
	else
	{
		if (str_is_digit(cmd->arg[1]))
			code = atoi(cmd->arg[1]);
		else
			return (write(2, "minishell: exit: ", 18), write(2, cmd->arg[1],
					ft_strlen(cmd->arg[1])), write(2,
					": numeric argument required\n", 28), 1);
		if (cmd->arg[2] != 0)
			return (write(2, "minishell: exit: too many arguments\n", 37), 1);
	}
	if (ex->cmd_pos == 0)
		dll(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr));
	else
		dll_child(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr));
	(dall(ex->cmd_ptr->va, ex->cmd_ptr->start), write(2, "exit\n", 5));
	if (tempfd != 0)
		(close(tempfd[0]), close(tempfd[1]));
	exit(code);
}
