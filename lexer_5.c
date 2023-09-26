/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:20:17 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:50:17 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "minishell.h"

static char	check_dq1(int i_op, char *str)
{
	int	count;
	int	count2;
	int	i;

	count = 1;
	i = -1;
	while (*(str + (++i)) && i != i_op)
		if (*(str + i) == '\"')
			++count;
	if (*(str + i) == 0)
		return (FAILURE);
	count2 = count;
	while (*(str + (++i)))
	{
		if (*(str + i) == '\"')
		{
			++count2;
			break ;
		}
	}
	if (count2 % 2 == 1 && count != count2)
		return (SUCCESS);
	return (FAILURE);
}

static char	check_q1(int i_op, char *str)
{
	int	count;
	int	count2;
	int	i;

	count = 1;
	i = -1;
	while (*(str + (++i)) && i != i_op)
		if (*(str + i) == '\'')
			++count;
	if (*(str + i) == 0)
		return (FAILURE);
	count2 = count;
	while (*(str + (++i)))
	{
		if (*(str + i) == '\'')
		{
			++count2;
			break ;
		}
	}
	if (count2 % 2 == 1 && count != count2)
		return (SUCCESS);
	return (FAILURE);
}

char	is_token(int i_op, int *i, char *str)
{
	if (*(str + i_op) == 0)
		return (FAILURE);
	if (char_is_token(*(str + i_op), *(str + i_op + 1), i) != SUCCESS)
		return (FAILURE);
	if ((check_dq1(i_op + 1, str) == FAILURE
			&& check_q1(i_op + 1, str) == FAILURE))
		return (SUCCESS);
	return (FAILURE);
}

char	fis_token(t_leaf *tr, char *str, int *i, int i_op)
{
	if (*(str + i_op) == 0)
		return (FAILURE);
	if (fchar_is_token(tr, str, i) != SUCCESS)
		return (FAILURE);
	if ((check_dq1(i_op + 1, str) == FAILURE
			&& check_q1(i_op + 1, str) == FAILURE))
		return (SUCCESS);
	return (FAILURE);
}

char	ris_token(int i_op, int *j, char *str)
{
	if (*(str + i_op) == 0)
		return (FAILURE);
	if (rev_char_is_token(*(str + i_op), *(str + i_op + 1), j) != SUCCESS)
		return (FAILURE);
	if ((check_dq1(i_op + 1, str) == FAILURE
			&& check_q1(i_op + 1, str) == FAILURE))
		return (SUCCESS);
	return (FAILURE);
}
