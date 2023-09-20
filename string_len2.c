/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_len2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:36 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/19 15:44:37 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

int	content_len2(char *str, int *i, t_lv *va)
{
	int	len;
	int	l;
	int	var_len;

	len = 0;
	l = 0;
	var_len = 0;
	++(*i);
	while (str[*i + len] && !is_metachar(str[*i + len]))
		++len;
	if (len)
	{
		if (find_n_name(str + *i, va, &l, len) == SUCCESS)
		{
			var_len = ft_strlen1((*(va + l)).content);
			return ((*i) += len, var_len);
		}
		else
			return ((*i) += len, 0);
	}
	return (1);
}

unsigned int	string_len2(char *str, t_lv *va)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
			len += content_len2(str, &i, va);
		else
		{
			++i;
			++len;
		}
	}
	return (len);
}
