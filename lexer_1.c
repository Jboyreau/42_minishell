/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:48:54 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:48:57 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

char	char_is_token(char c0, char c1, int *i)
{
	char *t;

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
		while (j > -1 && *(str + j) != '$' && *(str + j) != ' ' &&
		rev_char_is_token(*(str + j), *(str + j + 1), &j) == FAILURE)
			--j;
		if (j > 0)
			if ((*str + j) == '$')
				(++(*i), test = 0);
	}
	while (*(str + (*i)))
	{
		if (*(str + (*i)) == ' ' || (*(str + (*i)) == '$' && test == 0))
			return (++(*count), (void)0);
		if (char_is_token(*(str + (*i)), *(str + (*i) + 1), i) == SUCCESS)
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
	while (char_is_token(str[j], str[j + 1], &b) == 1 && *(str + j) != ' ')
		++j;	
	if (*(str + j) == '\n')
		return (normal_string(str, i, count));
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
	while (char_is_token(str[j], str[j + 1], &b) == 1 && *(str + j) != ' ')
		++j;
	if (*(str + j) == '\n')
		return (normal_string(str, i, count));
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
