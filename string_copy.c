/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:54 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 16:01:18 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define D_QUOTE '"'
#define S_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

/*
void	cpy_tab(char *content, int index, t_string *str)
{
	int	i;
	int	space_count;

	i = 1;
	space_count = 0;
	while (*(content + i++) == ' ')
		;
	while (*(content + i++) != ')')
	{
		if (index = space_count)
		{
			while (*(content + i++) == ')')
				*((*str).content + ((*str).cursor++)) = *(content + i);
			return ;
		}
		if (*(content + i) == ' ')
		{
			space_count++;
			while (*(content + i++) == ' ')
				;
		}
	}
}
*/

char	content_cpy(t_leaf *tok, int *i, t_lv *va, t_string *str)
{
	int	len;
	int	l;
	int	j;
	int	content_len;

	j = 0;
	len = 0;
	l = 0;
	content_len = 0;
	++(*i);
	if (*(tok->word + *i) == '?')
		return (ft_putnbr_q(g_signal, str), ++(*i), SUCCESS);
	while (!is_metachar(*(tok->word + *i + len)) && *i + len < tok->len)
		++len;
	if (len == 0)
		return (*((*str).content + ((*str).cursor++)) = '$', SUCCESS);
	if (find_n_name(tok->word + *i, va, &l, len) == SUCCESS)
	{
		content_len = ft_strlen((*(va + l)).content);
		while (content_len--)
			*((*str).content + ((*str).cursor++))
				= *((*(va + l)).content + j++);
	}
	return ((*i) += len, SUCCESS);
}

char	quote_cpy(t_leaf *tok, int *i, t_lv *va, t_string *str)
{
	int		len;
	char	quote_type;

	quote_type = *(tok->word + (*i)++);
	len = 0;
	while (*(tok->word + *i + len) != quote_type && *i + len < tok->len)
		++len;
	if (*(tok->word + *i + len) != quote_type)
		return ((*((*str).content + ((*str).cursor++)) = quote_type), SUCCESS);
	if (len == 0)
		return (++(*i));
	if (quote_type != D_QUOTE)
	{
		while (*(tok->word + *i) != S_QUOTE && *i < tok->len)
			*((*str).content + ((*str).cursor++)) = *(tok->word + (*i)++);
		return (++(*i), SUCCESS);
	}
	while (*(tok->word + *i) != D_QUOTE && *i < tok->len)
	{
		if (*(tok->word + *i) == '$')
			content_cpy(tok, i, va, str);
		else
			*((*str).content + ((*str).cursor++)) = *(tok->word + (*i)++);
	}
	return (++(*i), SUCCESS);
}

char	string_cpy(t_leaf *tok, t_lv *va, t_string *str)
{
	int	i;

	i = 0;
	while (i < tok->len)
	{
		if (*(tok->word + i) == D_QUOTE || *(tok->word + i) == S_QUOTE)
			quote_cpy(tok, &i, va, str);
		else if (*(tok->word + i) == '$')
			content_cpy(tok, &i, va, str);
		else
		{
			*((*str).content + ((*str).cursor++)) = *(tok->word + i);
			++i;
		}
	}
	*((*str).content + ((*str).cursor)) = 0;
	return (SUCCESS);
}
