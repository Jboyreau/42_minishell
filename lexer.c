/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:35:37 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 16:17:31 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> //debug
#include <unistd.h> //debug
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

void	fill_leaf(t_leaf *tr, char type, int len, char *word)
{
	(*tr).type = type;
	(*tr).len = len;
	(*tr).word = word;
	(*tr).f_type = 0;
	(*tr).fdl = 0;
	(*tr).arg = 0;
}

static void	fill_tree(char *str, t_leaf *tr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(str + i))
	{
		while (*(str + i) == ' ')
			++i;
		if (*(str + i) == 0)
			break ;
		if (*(str + i) && fis_token(tr + count, str, &i, i) == SUCCESS)
			++count;
		else
			flongest_token(tr + count, str, &i, &count);
	}
}

static int	token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(str + i))
	{
		while (*(str + i) == ' ')
			++i;
		if (*(str + i) == 0)
			break ;
		if (is_token(i, &i, str) == SUCCESS)
			++count;
		else
			longest_token(str, &i, &count);
	}
	return (count);
}

t_leaf	*lexer(t_cmd *hll)
{
	if ((*hll).str == NULL)
		return (NULL);
	(*hll).count = token_count((*hll).str) + 2;
	(*hll).tr = malloc((*hll).count * sizeof(t_leaf));
	if ((*hll).tr == NULL)
		return (NULL);
	fill_tree((*hll).str, (*hll).tr);
	fill_leaf((*hll).tr + (*hll).count - 1, -1, 0, NULL);
	fill_leaf((*hll).tr + (*hll).count - 2, NL, 0, NULL);
	return ((*hll).tr);
}
