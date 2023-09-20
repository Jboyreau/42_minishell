/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:08:25 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 15:03:01 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	ft_cd(t_leaf *cmd)
{
	int		i;

	i = 1;
	if ((cmd->arg[i]) == 0)
	{
		write(2, "minishell: cd: not enough arguments\n", 37);
		return (1);
	}
	i++;
	if (cmd->arg[i] != NULL)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (chdir(cmd->arg[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
