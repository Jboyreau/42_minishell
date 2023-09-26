/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:37:25 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:49:56 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

static char	fchar_is_token2(t_leaf *tr, char *str, int *i)
{
	if (*(str + (*i)) == ')')
		return (fill_leaf(tr, CLS_PAR, 1, str + (*i)), ++(*i), SUCCESS);
	if (*(str + (*i)) == '(')
		return (fill_leaf(tr, OP_PAR, 1, str + (*i)), ++(*i), SUCCESS);
	if (*(str + (*i)) == '\n')
		return (fill_leaf(tr, NL, 1, str + (*i)), ++(*i), SUCCESS);
	return (FAILURE);
}

char	fchar_is_token(t_leaf *tr, char *str, int *i)
{
	if (*(str + (*i)) == '<')
	{
		if (*(str + (*i)) == *(str + (*i) + 1))
			return (fill_leaf(tr, DL, 2, str + (*i)), (*i) += 2, SUCCESS);
		return (fill_leaf(tr, L, 1, str + (*i)), ++(*i), SUCCESS);
	}
	if (*(str + (*i)) == '>')
	{
		if (*(str + (*i)) == *(str + (*i) + 1))
			return (fill_leaf(tr, DR, 2, str + (*i)), (*i) += 2, SUCCESS);
		return (fill_leaf(tr, R, 1, str + (*i)), ++(*i), SUCCESS);
	}
	if (*(str + (*i)) == '|' )
	{
		if (*(str + (*i)) == *(str + (*i) + 1))
			return (fill_leaf(tr, OR, 2, str + (*i)), (*i) += 2, SUCCESS);
		return (fill_leaf(tr, PIPE, 1, str + (*i)), ++(*i), SUCCESS);
	}
	if (*(str + (*i)) == '&')
		if (*(str + (*i)) == *(str + (*i) + 1))
			return (fill_leaf(tr, AND, 2, str + (*i)), (*i) += 2, SUCCESS);
	return (fchar_is_token2(tr, str, i));
}
