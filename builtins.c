/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:33:01 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 11:46:03 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static const char	*g_builtin_cmd[7] = {
	"echo",
	"env",
	"cd",
	"export",
	"pwd",
	"unset",
	"exit"
};

static const char	*g_nofork_built[5] = {
	"env",
	"cd",
	"export",
	"unset",
	"exit"
};

void	builtins_exec(t_leaf *cmd, int builtin_index, t_exec *ex)
{
	int	exit_code;

	exit_code = 0;
	if (builtin_index == 0)
		exit_code = ft_echo(cmd);
	else if (builtin_index == 1)
		exit_code = env(ex->cmd_ptr->va);
	else if (builtin_index == 2)
		exit_code = ft_cd(cmd, &ex->cmd_ptr->va, ex->env);
	else if (builtin_index == 3)
		exit_code = builtin_export(&ex->cmd_ptr->va, ex->env, cmd);
	else if (builtin_index == 4)
		exit_code = ft_pwd();
	else if (builtin_index == 5)
		exit_code = unset(ex->cmd_ptr->va, cmd->arg);
	else if (builtin_index == 6)
		exit_code = ft_exit(cmd, ex, 0);
	(dll_child(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr)),
		dall(ex->cmd_ptr->va, ex->cmd_ptr->start));
	if (exit_code == 0)
		exit(0);
	else
		exit(1);
}

int	nofork_builtins_exec(t_leaf *cmd, int i, t_exec *ex)
{
	int	j;
	int	exit_code;
	int	temp_fd[2];

	j = -1;
	while (++j < 5)
		if (ft_strncmp((cmd + i)->word, g_nofork_built[j], (cmd + i)->len) == 0)
			break ;
	temp_fd[0] = dup(STDIN_FILENO);
	temp_fd[1] = dup(STDOUT_FILENO);
	if (pre_redir(cmd, i - 2, ex) == -1 || suf_redir(cmd + i, ex) == -1)
		return (1);
	if (j == 0)
		exit_code = env(ex->cmd_ptr->va);
	if (j == 1)
		exit_code = ft_cd(cmd + i, &ex->cmd_ptr->va, ex->env);
	if (j == 2)
		exit_code = builtin_export(&ex->cmd_ptr->va, ex->env, cmd + i);
	else if (j == 3)
		exit_code = unset(ex->cmd_ptr->va, (cmd + i)->arg);
	else if (j == 4)
		exit_code = ft_exit(cmd + i, ex, temp_fd);
	(dup2(temp_fd[0], STDIN_FILENO), dup2(temp_fd[1], STDOUT_FILENO));
	(close(temp_fd[0]), close(temp_fd[1]));
	return (exit_code);
}

char	is_nofork_builtin(t_leaf *cmd)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(cmd->word, g_nofork_built[i], cmd->len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	builtins_check(t_leaf *cmd, t_exec *ex)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd->word, g_builtin_cmd[i], cmd->len) == 0)
			builtins_exec(cmd, i, ex);
		i++;
	}
}
