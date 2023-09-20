/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:16 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 16:31:32 by cbessonn         ###   ########.fr       */
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

int subindex = 0; //----------------------------------------debug a enlever

void execute_built_in(t_leaf *tree, t_lv *va)
{
	int	i;
	int j;
	static char	*str = "export";

	i = -1;
	while ((*(tree + (++i))).type != -1)
	{
		j = -1;
		if ((*(tree + i)).len == EXPORT_LEN)
		{
			if ((*(tree + i)).type == W && (*(tree + i)).f_type == CMD)
			{
				while (++j < (*(tree + i)).len && *(str + j))
					if (*(str + j) != *((*(tree + i)).word + j))
						break ;
				if (*(str + j) == 0)
					print_va(va);
			}
		}
	}
}

void	clean_prompt(t_leaf **token)
{
	int	i;
	int	j;

	i = 0;
	while ((*(*token + i)).type != -1)
	{
		while ((*(*token + i)).type == NL)
		{
			j = i;
			while ((*(*token + j)).type != -1)
			{
				*(*token + j) = *(*token + j + 1);
				j++;
			}
		}
		if ((*(*token + i)).type != -1)
			i++;
	}
}

char	has_pipe_before(t_leaf *token, int i)
{
	while (i >= 0 && token[i].type != OP_PAR && token[i].type != AND 
		&& token[i].type != OR)
	{
		if (token[i].type == PIPE)
			return (1);
		i--;
	}
	return (0);
}

char	check_sub_pos(t_leaf *token, int fpar, int lpar)
{
	char pipe[2];

	pipe[0] = has_pipe_before(token, fpar - 1);
	pipe[1] = 0;
	lpar++;
	while (token[lpar].type != -1 && token[lpar].type != CLS_PAR
		&& token[lpar].type != AND && token[lpar].type != OR)
	{
		if (token[lpar].type == PIPE)
		{
			pipe[1] = 1;
			break ;
		}
		lpar++;
	}
	if (pipe[0] == 0 && pipe[1] == 0)
		return (NO_PIPE);
	else if (pipe[0] == 1 && pipe[1] == 0)
		return (LAST_CMD);
	else if (pipe[0] == 0 && pipe[1] == 1)
		return (FIRST_CMD);
	return (MID_CMD);
}

char	check_cmd_pos(t_leaf *token, int i)
{
	char pipe[2];

	pipe[0] = has_pipe_before(token, i);
	pipe[1] = 0;
	while (token[i].type != -1 && token[i].type != CLS_PAR
		&& token[i].type != AND && token[i].type != OR)
	{
		if (token[i].type == PIPE)
		{
			pipe[1] = 1;
			break ;
		}
		i++;
	}
	if (pipe[0] == 0 && pipe[1] == 0)
		return (NO_PIPE);
	else if (pipe[0] == 1 && pipe[1] == 0)
		return (LAST_CMD);
	else if (pipe[0] == 0 && pipe[1] == 1)
		return (FIRST_CMD);
	return (MID_CMD);
}

int	wait_cmd(int nb_of_cmd, pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		i;
	int		save_status;

	i = 0;
	(sigint_handler(-4));
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
	(sigint_handler(-3));
	if (save_status == 0)
		return (0);
	if ((save_status & 255) != 0)
		return ((save_status & 255) + 128);
	return ((status >> 8) + 125);
}

void	last_par(t_leaf *token, int *i)
{
	int	count;

	count = 1;
	++(*i);
	while (1)
	{
		if (token[*i].type == OP_PAR)
			count++;
		else if (token[*i].type == CLS_PAR)
			count--;
		if (count == 0)
			break ;
		++(*i);
	}
}

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
		ex->status = wait_cmd(ex->nb_of_cmd, ex->last_pid);
	token[*i].type = CLS_PAR;
}

int	execute_sub(t_cmd *hll, t_leaf *token, int i, char **env)
{
	static int	pipefd[3];
	t_exec	ex;

	ex.env = env;
	ex.cmd_ptr = hll;
	while (token[i].type != -1)
	{
		if (token[i].type == W && token[i].f_type == CMD)
		{
			ex.cmd_pos = check_cmd_pos(token, i);
			if (ex.cmd_pos == FIRST_CMD || ex.cmd_pos == NO_PIPE)
				ex.nb_of_cmd = 0;
			ex.nb_of_cmd++;
			ex.last_pid = exec_pipeline(token, &ex, i, pipefd);
			if (ex.cmd_pos == NO_PIPE || ex.cmd_pos == LAST_CMD)
				ex.status = wait_cmd(ex.nb_of_cmd, ex.last_pid);
		}
		else if (token[i].type == OP_PAR)
			handle_subshell(token, &i, pipefd, &ex);
		else if ((token[i].type == AND && ex.status != 0) || (token[i].type == OR && ex.status == 0))
		{
			i++;
			if (token[i].type == OP_PAR)
				last_par(token, &i);
		}
		i++;
	}
	exit(ex.status);
}

void	execute(t_cmd *hll, t_leaf *token, char **env)
{
	int		i;
	t_exec	ex;
	static int	pipefd[3];

	ex.env = env;
	ex.cmd_ptr = hll;
	i = 0;
	while (token[i].type != -1)
	{
		if (token[i].type == W && token[i].f_type == CMD)
		{
			ex.cmd_pos = check_cmd_pos(token, i);
			if (ex.cmd_pos == FIRST_CMD || ex.cmd_pos == NO_PIPE)
				ex.nb_of_cmd = 0;
			ex.nb_of_cmd++;
			if (ex.cmd_pos == NO_PIPE && is_nofork_builtin(token + i))
				ex.status = nofork_builtins_exec(token, i, &ex);
			else
			{
				ex.last_pid = exec_pipeline(token, &ex, i, pipefd);
					if (ex.cmd_pos == NO_PIPE || ex.cmd_pos == LAST_CMD)
						ex.status = wait_cmd(ex.nb_of_cmd, ex.last_pid);
			}
		}
		else if (token[i].type == OP_PAR)
			handle_subshell(token, &i, pipefd, &ex);
		else if ((token[i].type == AND && ex.status != 0) || (token[i].type == OR && ex.status == 0))
		{
			while (token[i].type != -1 && token[i + 1].type != AND && token[i + 1].type != OR)
			{
				i++;
				if (token[i].type == OP_PAR)
					last_par(token, &i);
			}
		}
		i++;
	}
}
