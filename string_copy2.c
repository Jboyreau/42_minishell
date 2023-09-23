/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:47 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 15:58:52 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

char	content_cpy2(char **str, int *i, t_lv *va, t_string *new)
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
	if (*((*str) + *i) == '?')
		return (ft_putnbr_q(g_signal, new), ++(*i), SUCCESS);
	while (!is_metachar((*str)[*i + len]) && (*str)[*i + len])
		++len;
	if (len == 0)
		return (*((*new).content + ((*new).cursor++)) = '$', SUCCESS);
	if (find_n_name((*str) + *i, va, &l, len) == SUCCESS)
	{
		content_len = ft_strlen1((*(va + l)).content);
		while (content_len--)
			*((*new).content + ((*new).cursor++))
				= *((*(va + l)).content + j++);
	}
	return ((*i) += len, SUCCESS);
}

char	string_cpy2(char **str, t_lv *va, t_string *new)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			content_cpy2(str, &i, va, new);
		else
		{
			*((*new).content + ((*new).cursor++)) = (*str)[i];
			++i;
		}
	}
	*((*new).content + ((*new).cursor)) = 0;
	return (SUCCESS);
}
