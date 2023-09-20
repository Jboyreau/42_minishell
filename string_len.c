/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:41 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/19 15:44:41 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

int	content_len(t_leaf *tok, int *i, t_lv *va)
{
	int	len;
	int	l;
	int	var_len;

	len = 0;
	l = 0;
	var_len = 0;
	++(*i);
	while (!is_metachar(*(tok->word + *i + len)) && *i + len < tok->len)
		++len;
	if (len)
	{
		if (find_n_name(tok->word + *i, va, &l, len) == SUCCESS)
		{
			var_len = ft_strlen((*(va + l)).content);
			return ((*i) += len, var_len);
		}
		else
			return ((*i) += len, 0);
	}
	return (1);
}

// int is_complete_quote(t_leaf *tok, int i, char quote_type)
// {
// 	while (*(tok->word + i) != quote_type && i < tok->len)
// 		++i;
// 	return (i);
// }

int	quote_len(t_leaf *tok, int *i, char quote_type, t_lv *va)
{
	int	len;
	int	var_len;

	len = 0;
	var_len = 0;
	++(*i);
	while (*(tok->word + *i + len) != quote_type && *i + len < tok->len)
		len++;
	if (*(tok->word + *i + len) != quote_type) //if is incomplete quote, return the size of 1 char (for the actual quote not being interpreted)
		return (1);
	if (quote_type == DOUBLE_QUOTE) //if double quote we need to expand
	{
		while (*(tok->word + *i) != DOUBLE_QUOTE && *i < tok->len)
		{
			if (*(tok->word + *i) == '$')
				var_len += content_len(tok, i, va);
			else
				(*i)++;
		}
		return (len + var_len);
	}
	return ((*i) += len + 1, len + var_len);
}

unsigned int	string_len(t_leaf *tok, t_lv *va)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < tok->len)
	{
		if (*(tok->word + i) == DOUBLE_QUOTE || *(tok->word + i) == SIMPLE_QUOTE)
		{
			len += quote_len(tok, &i, *(tok->word + i), va);
		}
		else if (*(tok->word + i) == '$')
			len += content_len(tok, &i, va);
		else
		{
			++i;
			++len;
		}
	}
	return (len);
}
