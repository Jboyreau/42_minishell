/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:14 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 12:33:31 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define NO_PIPE 0
#define FIRST_CMD 1
#define MID_CMD 2
#define LAST_CMD 3

void	open_pipe(int *pipefd, char cmd_pos, t_cmd *hll)
{
	if (cmd_pos != LAST_CMD)
	{
		if (pipe(pipefd) == -1)
			exit_failure(hll);
	}
}

void	redirect_pipe(int *pipefd, char cmd_pos)
{
	if (cmd_pos == FIRST_CMD)
		dup2(pipefd[1], STDOUT_FILENO);
	else if (cmd_pos == LAST_CMD)
		dup2(pipefd[2], STDIN_FILENO);
	else if (cmd_pos == MID_CMD)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipefd[2], STDIN_FILENO);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(pipefd[2]);
}

pid_t	exec_pipeline(t_leaf *cmd, t_exec *ex, int i, int *pipefd)
{
	pid_t		pid;

	if (ex->cmd_pos == FIRST_CMD)
		pipefd[2] = dup(STDIN_FILENO);
	if (ex->cmd_pos != NO_PIPE)
		open_pipe(pipefd, ex->cmd_pos, ex->cmd_ptr);
	pid = fork();
	if (pid == -1)
		exit_failure(ex->cmd_ptr);
	else if (pid == 0)
	{
		(sigint_handler(-2), sigquit_handler(-2));
		if (ex->cmd_pos != NO_PIPE)
			redirect_pipe(pipefd, ex->cmd_pos);
		exec_cmd(cmd, i, ex);
	}
	if (ex->cmd_pos != NO_PIPE)
	{
		(close(pipefd[1]), close(pipefd[2]));
		pipefd[2] = pipefd[0];
	}
	if (ex->cmd_pos == LAST_CMD)
		close(pipefd[2]);
	return (pid);
}
