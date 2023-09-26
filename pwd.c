/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:07:55 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 21:58:48 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	ft_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	else
	{
		if (write(STDOUT_FILENO, &buffer, ft_strlen(buffer)) == -1)
			return (perror("bash: pwd: write error:No space left on device"),
				-1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("bash: pwd: write error: No space left on device"),
				-1);
	}
	return (0);
}
