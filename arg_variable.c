/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:51:12 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 16:00:18 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

char	split_args(t_leaf *cmd, t_leaf *token, t_lv *va)
{
	char		*arg;
	t_str_array	array;
	int			i;

	i = -1;
	arg = string_sub(token, va);
	if (arg == NULL)
		return (FAILURE);
	if (ft_split(&array, arg, ' ') == false)
		return (free(arg), FAILURE);
	free(arg);
	if (array.ptr[0] == 0)
		return (free(array.ptr), args_to_array_wildcard(cmd, "\0"), SUCCESS);
	while (++i < array.size)
	{
		if (args_to_array_wildcard(cmd, array.ptr[i]) == FAILURE)
			return (free_array(array.ptr), FAILURE);
	}
	free_array(array.ptr);
	return (SUCCESS);
}
