/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:35:25 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:49:48 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

char	char_is_token(char c0, char c1, int *i)
{
	char	*t;

	t = ")\n(<>|";
	if ((c0 == '<' || c0 == '>' || c0 == '|' || c0 == '&') && (c0 == c1))
		return ((*i) += 2, SUCCESS);
	while (*t)
	{
		if (c0 == *t)
			return (++(*i), SUCCESS);
		++t;
	}
	return (FAILURE);
}

static void	normal_string(char *str, int *i, int *count)
{
	int	j;
	int	test;

	test = 1;
	if (*(str + (*i)) == '$')
	{
		j = *i;
		while (j > -1 && *(str + j) != '$' && is_space(j, str)
			&& ris_token(j, &j, str) == FAILURE)
			--j;
		if (j > 0 && ((*str + j) == '$'))
		{
			++(*i);
			test = 0;
		}
	}
	while (*(str + (*i)))
	{
		if (is_space(*i, str) || (*(str + (*i)) == '$' && test == 0))
			return (++(*count), (void)0);
		if (is_token(*i, i, str) == SUCCESS)
			return (*count += 2, (void)0);
		++(*i);
	}
	return (++(*count), (void)0);
}

static void	dq_sequence(char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\"' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (normal_string(str, i, count));
	while (is_token(j, &b, str) == 1 && is_space(j, str) == 0)
	{
		++j;
		if (*(str + j) == 0)
			break ;
	}
	return (*i = j, ++(*count), (void)0);
}

static void	q_sequence(char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\'' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (normal_string(str, i, count));
	while (is_token(j, &b, str) == 1 && is_space(j, str) == 0)
	{
		++j;
		if (*(str + j) == 0)
			break ;
	}
	return (*i = j, ++(*count), (void)0);
}

void	longest_token(char *str, int *i, int *count)
{
	if (*(str + (*i)) == '\'')
		return (q_sequence(str, i, count));
	if (*(str + (*i)) == '\"')
		return (dq_sequence(str, i, count));
	return (normal_string(str, i, count));
}
