/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:07:55 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 16:07:15 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	ft_pwd(void)
{
	char buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	else
	{
		if (write(STDOUT_FILENO, &buffer, ft_strlen(buffer)) == -1)
			perror("write error");
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			perror("write error");
	}
	return (0);
}
