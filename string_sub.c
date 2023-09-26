/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:26 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 16:00:59 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	find_n_name(char *name, t_lv *va, int *l, int n)
{
	int	i;
	int	j;

	i = -1;
	while ((*(va + (++i))).name)
	{
		j = -1;
		while (*((*(va + i)).name + (++j)) && j < n)
			if (*((*(va + i)).name + j) != *(name + j))
				break ;
		if (*((*(va + i)).name + j) == 0 && n == j)
			return (*l = i, SUCCESS);
	}
	return (FAILURE);
}

char	is_metachar(char c)
{
	return (c == '"' || c == '\'' || c == '$' || c == '&'
		|| c == '|' || c == '<' || c == '>' || c == '@'
		|| c == '=' || c == '#' || c == '.' || c == '/'
		|| c == ',' || c == '%' || c == '-' || c == '*'
		|| c == '+' || c == '!' || c == ':'
		|| c == '~' || c == '^' || c == '{'
		|| c == '}' || c == '\\' || c == '['
		|| c == ']');
}

char	*string_sub(t_leaf *tok, t_lv *va)
{
	int			len;
	t_string	str;

	len = string_len(tok, va);
	str.cursor = 0;
	str.content = malloc(len + 1);
	if (str.content == NULL)
		return (NULL);
	if (len == 0)
		*(str.content) = '\0';
	else
		string_cpy(tok, va, &str);
	return (str.content);
}
