/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:55:31 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 14:58:14 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NO_PIPE 0
#define FIRST_CMD 1
#define MID_CMD 2
#define LAST_CMD 3

void	handle_subshell(t_leaf *token, int *i, int *pipefd, t_exec *ex)
{
	ex->save_first = *i;
	last_par(token, i);
	ex->sub_end = *i;
	ex->cmd_pos = check_sub_pos(token, ex->save_first, *i);
	if (ex->cmd_pos == FIRST_CMD || ex->cmd_pos == NO_PIPE)
		ex->nb_of_cmd = 0;
	ex->nb_of_cmd++;
	token[*i].type = -1;
	ex->last_pid = pipe_subshell(token, ex, pipefd);
	if (ex->last_pid == 0)
		execute_sub(ex->cmd_ptr, token, ex->save_first + 1, ex->env);
	if (ex->cmd_pos == NO_PIPE || ex->cmd_pos == LAST_CMD)
	{
		ex->status = wait_cmd(ex->nb_of_cmd, ex->last_pid);
		//update_exit_stat(ex->cmd_ptr->va, ex->status);
		g_signal = ex->status;
	}
	token[*i].type = CLS_PAR;
}

void	handle_sub_command(t_exec *ex, t_leaf *tok, int i, int *pipefd)
{
	ex->cmd_pos = check_cmd_pos(tok, i);
	if (ex->cmd_pos == FIRST_CMD || ex->cmd_pos == NO_PIPE)
		ex->nb_of_cmd = 0;
	ex->nb_of_cmd++;
	ex->last_pid = exec_pipeline(tok, ex, i, pipefd);
	if (ex->cmd_pos == NO_PIPE || ex->cmd_pos == LAST_CMD)
	{
		ex->status = wait_cmd(ex->nb_of_cmd, ex->last_pid);
		//update_exit_stat(ex->cmd_ptr->va, ex->status);
		g_signal = ex->status;
	}
}

int	execute_sub(t_cmd *hll, t_leaf *tok, int i, char **env)
{
	static int	pipefd[3];
	t_exec		ex;

	ex.env = env;
	ex.cmd_ptr = hll;
	while (tok[i].type != -1)
	{
		if (tok[i].type == W && tok[i].f_type == CMD)
			handle_sub_command(&ex, tok, i, pipefd);
		else if (tok[i].type == OP_PAR)
			handle_subshell(tok, &i, pipefd, &ex);
		else if ((tok[i].type == AND && ex.status != 0)
			|| (tok[i].type == OR && ex.status == 0))
			if (tok[++i].type == OP_PAR)
				last_par(tok, &i);
		i++;
	}
	(dll(&(ex.cmd_ptr->str), &(ex.cmd_ptr->tr)),
		dall(ex.cmd_ptr->va, ex.cmd_ptr->start));
	exit(ex.status);
}

pid_t	pipe_subshell(t_leaf *cmd, t_exec *ex, int *pipefd)
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
		if (suf_redir(cmd + ex->sub_end + 1, ex) == -1)
			exit_failure(ex->cmd_ptr);
		if (ex->cmd_pos != NO_PIPE)
			redirect_pipe(pipefd, ex->cmd_pos);
		return (pid);
	}
	if (ex->cmd_pos != NO_PIPE)
		(close(pipefd[1]), close(pipefd[2]), pipefd[2] = pipefd[0]);
	if (ex->cmd_pos == LAST_CMD)
		close(pipefd[2]);
	return (pid);
}
