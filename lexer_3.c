/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:37:36 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:50:01 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

char	rev_char_is_token(char c0, char c1, int *j)
{
	char	*t;

	t = ")\n(<>|";
	if ((c0 == '<' || c0 == '>' || c0 == '|' || c0 == '&') && (c0 == c1))
		return ((*j) -= 2, SUCCESS);
	while (*t)
	{
		if (c0 == *t)
			return (--(*j), SUCCESS);
		++t;
	}
	return (FAILURE);
}

static void	fnormal_string(t_leaf *tr, char *str, int *i, int *count)
{
	int	s;
	int	j;
	int	test;

	s = *i;
	test = 1;
	if (*(str + (*i)) == '$')
	{
		j = *i;
		while (j > -1 && *(str + j) != '$' && is_space(j, str)
			&& ris_token(j, &j, str) == FAILURE)
			--j;
		if (j > 0 && (*str + j) == '$')
			++(*i);
		if (j > 0 && (*str + j) == '$')
			test = 0;
	}
	while (*(str + (*i)))
	{
		if (is_space(*i, str) || (*(str + (*i)) == '$' && test == 0))
			return (fill_leaf(tr, W, *i - s, str + s), ++(*count), (void)0);
		if (++(*i), is_token(*i, &j, str) == SUCCESS)
			return (fill_leaf(tr, W, *i - s, str + s), ++(*count), (void)0);
	}
	return (fill_leaf(tr, W, *i - s, str + s), ++(*count), (void)0);
}

static void	fdq_sequence(t_leaf *tr, char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\"' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (fnormal_string(tr, str, i, count));
	while (is_token(j, &b, str) == 1 && is_space(j, str) == 0)
	{
		++j;
		if (*(str + j) == 0)
			break ;
	}
	fill_leaf(tr, W, (j - (*i)), str + (*i));
	return (*i = j, ++(*count), (void)0);
}

static void	fq_sequence(t_leaf *tr, char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\'' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (fnormal_string(tr, str, i, count));
	while (is_token(j, &b, str) == 1 && is_space(j, str) == 0)
	{
		++j;
		if (*(str + j) == 0)
			break ;
	}
	fill_leaf(tr, W, (j - (*i)), str + (*i));
	return (*i = j, ++(*count), (void)0);
}

void	flongest_token(t_leaf *tr, char *str, int *i, int *count)
{
	if (*(str + (*i)) == '\'')
		return (fq_sequence(tr, str, i, count));
	if (*(str + (*i)) == '\"')
		return (fdq_sequence(tr, str, i, count));
	return (fnormal_string(tr, str, i, count));
}
