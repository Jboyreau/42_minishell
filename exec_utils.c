/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:56:04 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 17:56:42 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_PIPE 0
#define FIRST_CMD 1
#define MID_CMD 2
#define LAST_CMD 3

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
	char	pipe[2];

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
	char	pipe[2];

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
