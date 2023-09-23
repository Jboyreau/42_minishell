/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:37:32 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:39:56 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "minishell.h"

static char	check_dq(int i_space, char *str)
{
	int	count;
	int	count2;
	int	i;

	count = 1;
	i = -1;
	while (*(str + (++i)) && i != i_space)
		if (*(str + i) == '\"')
			++count;
	if (*(str + i) == 0)
		return (FAILURE);
	count2 = count;
	while (*(str + (++i)))
	{
		if (*(str + i) == '\"')
		{
			++count2;
			break ;
		}
	}
	if (count2 % 2 == 1 && count != count2)
		return (SUCCESS);
	return (FAILURE);
}

static char	check_q(int i_space, char *str)
{
	int	count;
	int	count2;
	int	i;

	count = 1;
	i = -1;
	while (*(str + (++i)) && i != i_space)
		if (*(str + i) == '\'')
			++count;
	if (*(str + i) == 0)
		return (FAILURE);
	count2 = count;
	while (*(str + (++i)))
	{
		if (*(str + i) == '\'')
		{
			++count2;
			break ;
		}
	}
	if (count2 % 2 == 1 && count != count2)
		return (SUCCESS);
	return (FAILURE);
}

char	is_space(int i_space, char *str)
{
	if (*(str + i_space) == 0)
		return (FAILURE);
	if (*(str + i_space) != ' ' && *(str + i_space) != '	')
		return (0);
	if ((check_dq(i_space + 1, str) == FAILURE
			&& check_q(i_space + 1, str) == FAILURE))
		return (1);
	return (0);
}
