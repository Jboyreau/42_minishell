/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:01 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 12:33:49 by cbessonn         ###   ########.fr       */
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

void	exec_path(char *cmd_with_path, t_leaf *cmd, t_exec *ex, char *new_cmd)
{
	int	er;

	if (execve(cmd_with_path, cmd->arg, ex->env) == -1)
	{
		er = errno;
		if (errno == ENOENT)
		{
			write(2, (cmd)->arg[0], ft_strlen(cmd->arg[0]));
			write(2, ": command not found\n", 21);
		}
		else
			perror("");
		return (free(cmd_with_path), free(new_cmd),
			exit(er + 125));
	}
}

void	exec_with_path(t_leaf *cmd, t_str_array *paths,
t_exec *ex, char *new_cmd)
{
	int		i;
	char	*cmd_with_path;

	i = -1;
	while (paths->ptr[++i])
	{
		cmd_with_path = ft_strjoin(paths->ptr[i], new_cmd);
		if (cmd_with_path == 0)
			exit_failure(ex->cmd_ptr);
		cmd->arg[0] = cmd_with_path;
		if (access(cmd_with_path, F_OK) == 0)
			exec_path(cmd_with_path, cmd, ex, new_cmd);
		free(cmd_with_path);
	}
}

void	test_cmd_with_paths(char *cmd_name,
t_leaf	*cmd, t_str_array *paths, t_exec *ex)
{
	char	*new_cmd;
	char	*save_cmd;

	save_cmd = cmd->arg[0];
	new_cmd = ft_strjoin("/", cmd_name);
	if (new_cmd == 0)
		exit_failure(ex->cmd_ptr);
	if (paths->ptr)
	{
		exec_with_path(cmd, paths, ex, new_cmd);
		ft_str_array_free(paths);
	}
	free(new_cmd);
	cmd->arg[0] = save_cmd;
}

void	get_paths(t_str_array *array, t_exec *ex, t_leaf *cmd)
{
	int	i;

	i = 0;
	while (ex->cmd_ptr->va[i].name)
	{
		if (ft_strncmp(ex->cmd_ptr->va[i].name, "PATH", 4) == 0)
			break ;
		i++;
	}
	if (ex->cmd_ptr->va[i].name == 0)
		return ;
	if (ft_split(array, ex->cmd_ptr->va[i].content, ':') == false)
		return (exit_failure(ex->cmd_ptr));
	if (*((cmd)->arg[0]) != '/' && *((cmd)->arg[0]) != '.')
		test_cmd_with_paths(cmd->arg[0], cmd, array, ex);
	else
		ft_str_array_free(array);
}

void	exec_cmd(t_leaf	*cmd, int i, t_exec *ex)
{
	t_str_array	paths;
	int			er;

	if (ex->redir_alone)
		redirect_alone(cmd, i, ex);
	if (pre_redir(cmd, i - 2, ex) == -1 || suf_redir(cmd + i, ex) == -1
		|| *((cmd + i)->arg[0]) == '\0')
		(dll_child(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr)),
			dall(ex->cmd_ptr->va, ex->cmd_ptr->start), exit(1));
	builtins_check(cmd + i, ex);
	get_paths(&paths, ex, cmd + i);
	er = 0;
	if (execve((cmd + i)->arg[0], (cmd + i)->arg, ex->env) == -1)
	{
		er = errno;
		if (er == ENOENT)
			(write(2, (cmd + i)->arg[0], ft_strlen((cmd + i)->arg[0])),
				write(2, ": command not found\n", 21));
		else
			perror("");
	}
	(dll_child(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr)),
		dall(ex->cmd_ptr->va, ex->cmd_ptr->start));
	exit(er + 125);
}
