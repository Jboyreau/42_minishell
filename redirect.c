/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:27:11 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 14:52:02 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	aft_redir(t_leaf *token)
{
	while (token->type != -1)
	{
		if (token->type == L || token->type == DR || token->type == R)
		{
			token += 2;
			continue ;
		}
		else if (token->type == W)
			return (FAILURE);
		else
			return (SUCCESS);
	}
	return (SUCCESS);
}

char	bef_redir(t_leaf *token, int i)
{
	int	first_redir;

	first_redir = -1;
	while (i >= 0 && (token[i].type == L || token[i].type == DR
			|| token[i].type == R))
	{
		first_redir = i;
		i -= 2;
	}
	if (i == -1)
		return (FAILURE);
	if (first_redir == 0)
		return (SUCCESS);
	if (token[first_redir - 1].type == W
		|| token[first_redir - 1].type == CLS_PAR)
		return (FAILURE);
	return (SUCCESS);
}

void	redirect_alone(t_leaf *redirect, int i, t_exec *ex)
{
	int	fd;

	while (redirect[i].type != -1 && (redirect[i].type == L
			|| redirect[i].type == DR || redirect[i].type == R))
	{
		fd = open_file((redirect + i + 1), redirect + i,
				ex->cmd_ptr->va, ex->cmd_ptr);
		if (fd == -1)
			break ;
		close(fd);
		i += 2;
	}
	(dll_child(&(ex->cmd_ptr->str), &(ex->cmd_ptr->tr)),
		dall(ex->cmd_ptr->va, ex->cmd_ptr->start));
	exit(0);
}

void	check_if_cmd(t_leaf *token, int *i, t_exec *ex, int *pipefd)
{
	int	temp;

	temp = *i;
	if (aft_redir(token + *i) == SUCCESS && bef_redir(token, *i) == SUCCESS)
	{
		ex->redir_alone = 1;
		while (token[*i].type != -1)
		{
			if (token[*i].type == L || token[*i].type == DR
				|| token[*i].type == R)
				(*i) += 2;
			else
				break ;
		}
		handle_command(ex, token, temp, pipefd);
	}
}
