/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:01 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 16:49:47 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h> //----------------------Debug

bool	get_paths(t_str_array *array, t_lv *va)
{
	int	i;

	i = 0;
	while (va[i].name)
	{
		if (ft_strncmp(va[i].name, "PATH", 4) == 0)
			break ;
		i++;
	}
	if (ft_split(array, va[i].content, ':') == false)
		return (false);
	return (true);
}

void	test_cmd_with_paths(char *cmd_name, t_leaf	*cmd, t_str_array *paths, t_exec *ex)
{
	int		i;
	char	*cmd_with_path;
    char	*new_cmd;
	int		errno_code;
	char	*save_cmd;

	save_cmd = cmd->arg[0];
	i = 0;
	new_cmd = ft_strjoin("/", cmd_name);
	if (paths->ptr)
	{
		while (paths->ptr[i])
		{
			cmd_with_path = ft_strjoin(paths->ptr[i], new_cmd);
			cmd->arg[0] = cmd_with_path;
			//fprintf(stderr, "test ------ %s\n",);
			if (access(cmd_with_path, F_OK) == 0)
				if (execve(cmd_with_path, cmd->arg, ex->env) == -1)
				{
					errno_code = errno;
					return (free(cmd_with_path), free(new_cmd), exit(125 + errno_code));
				}
			free(cmd_with_path);
			i++;
		}
		ft_str_array_free(paths);
	}
	free(new_cmd);
	cmd->arg[0] = save_cmd;
}

void	exec_cmd(t_leaf	*cmd, int i, t_exec *ex)
{
	t_str_array paths;
	
	prefix_redirect(cmd, i - 2, ex);
	suffix_redirect(cmd + i, ex);
	builtins_check(cmd + i, ex);
	get_paths(&paths, ex->cmd_ptr->va);
	if (*((cmd + i)->arg[0]) != '/')
		test_cmd_with_paths((cmd + i)->arg[0], cmd + i, &paths, ex);
	if (access((cmd + i)->arg[0], F_OK) == 0)
		execve((cmd + i)->arg[0], (cmd + i)->arg, ex->env);
   	//fprintf(stderr, "something went wrong with execve()! %s\n", strerror(errno));
	(dll(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr)), dall(ex->cmd_ptr->va, ex->cmd_ptr->start));
	exit(125 + errno);
}
