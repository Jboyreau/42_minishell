/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:08:25 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 18:00:33 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdlib.h>

int	update_pwd(t_lv **va, char **env, const char *var_name, int len)
{
	char	*str;
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (perror("getcwd error"), -1);
	str = ft_strjoin(var_name, buffer);
	ft_export(va, env, str, ft_strlen(str) + len);
	free(str);
	return (0);
}

int	ft_cd(t_leaf *cmd, t_lv **va, char **env)
{
	int	i;
	int	len;

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
	if (find_name("OLDPWD", *va, &len) == SUCCESS)
		update_pwd(va, env, "OLDPWD=", 7);
	if (chdir(cmd->arg[1]) != 0)
		return (perror("cd"), 1);
	if (find_name("PWD", *va, &len) == SUCCESS)
		update_pwd(va, env, "PWD=", 4);
	return (0);
}
