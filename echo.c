/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 04:22:20 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 12:42:20 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	check_line_break_option(char **args, int *no_line_return)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
				return (i);
			j++;
		}
		*no_line_return = 1;
		i++;
	}
	return (i);
}

int	ft_echo(t_leaf *cmd)
{
	int		no_line_return;
	int		i;
	char	**args;

	args = cmd->arg + 1;
	no_line_return = 0;
	i = check_line_break_option(args, &no_line_return);
	while (args[i] != NULL)
	{
		if (write(STDOUT_FILENO, args[i], strlen(args[i])) == -1)
			perror("write error");
		if (args[i + 1] != NULL)
			if (write(STDOUT_FILENO, " ", 1) == -1)
				perror("write error");
		i++;
	}
	if (no_line_return == 0)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			perror("\n");
	return (0);
}
