/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:16 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 13:31:40 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define EXPORT_LEN 6

#define NO_PIPE 0
#define FIRST_CMD 1
#define MID_CMD 2
#define LAST_CMD 3

int	wait_cmd_sub(int nb_of_cmd, pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		i;
	int		save_status;

	i = 0;
	sigint_handler(-4);
	while (i < nb_of_cmd)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			save_status = status;
		i++;
	}
	if (save_status == 2)
		write(2, "\n", 1);
	if (save_status == 131)
		write(2, "\nQuit (core dumped)\n", 21);
	sigint_handler(-3);
	return (save_status);
}

int	wait_cmd(int nb_of_cmd, pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		i;
	int		save_status;

	i = -1;
	sigint_handler(-4);
	while (++i < nb_of_cmd)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			save_status = status;
	}
	if (save_status < 0)
		return ((save_status * -1) >> 8);
	if (save_status == 2)
		write(2, "\n", 1);
	if (save_status == 131)
		write(2, "\nQuit (core dumped)\n", 21);
	sigint_handler(-3);
	if (save_status == 0)
		return (0);
	if ((save_status & 255) != 0)
		return ((save_status & 255) + 128);
	return ((save_status >> 8));
}

void	handle_command(t_exec *ex, t_leaf *token, int i, int *pipefd)
{
	ex->cmd_pos = check_cmd_pos(token, i);
	if (ex->cmd_pos == FIRST_CMD || ex->cmd_pos == NO_PIPE)
		ex->nb_of_cmd = 0;
	ex->nb_of_cmd++;
	if (ex->cmd_pos == NO_PIPE && is_nofork_builtin(token + i))
	{
		ex->status = nofork_builtins_exec(token, i, ex);
		g_signal = ex->status;
	}
	else
	{
		ex->last_pid = exec_pipeline(token, ex, i, pipefd);
		if (ex->cmd_pos == NO_PIPE || ex->cmd_pos == LAST_CMD)
		{
			ex->status = wait_cmd(ex->nb_of_cmd, ex->last_pid);
			g_signal = ex->status;
		}
	}
}

void	execute(t_cmd *hll, t_leaf *token, char **env)
{
	int			i;
	t_exec		ex;
	static int	pipefd[3];

	ex.env = env;
	ex.cmd_ptr = hll;
	ex.redir_alone = 0;
	i = -1;
	while (token[++i].type != -1)
	{
		if (token[i].type == L || token[i].type == R || token[i].type == DR)
			check_if_cmd(token, &i, &ex, pipefd);
		else if (token[i].type == W && token[i].f_type == CMD)
			handle_command(&ex, token, i, pipefd);
		else if (token[i].type == OP_PAR)
			handle_subshell(token, &i, pipefd, &ex);
		else if ((token[i].type == AND && ex.status != 0)
			|| (token[i].type == OR && ex.status == 0))
		{
			while (token[i].type != -1 && token[i + 1].type != AND
				&& token[i + 1].type != OR)
				if (token[++i].type == OP_PAR)
					last_par(token, &i);
		}
	}
}
