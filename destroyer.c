/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:00:22 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 14:42:34 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	destroy_arg_child(t_leaf *tr)
{
	int	i;
	int	j;

	i = -1;
	if (tr)
	{
		while ((*(tr + (++i))).type != -1)
		{
			if ((*(tr + i)).type == W && (*(tr + i)).f_type == CMD)
			{
				j = -1;
				while ((*(tr + i)).arg && *((*(tr + i)).arg + (++j)))
					free(*((*(tr + i)).arg + j));
				free((*(tr + i)).arg);
			}
			if ((*(tr + i)).type == DL && (*(tr + i + 1)).type == W)
				free((*(tr + i)).word);
		}
	}
}

void	destroy_arg(t_leaf *tr)
{
	int	i;
	int	j;

	i = -1;
	if (tr)
	{
		while ((*(tr + (++i))).type != -1)
		{
			if ((*(tr + i)).type == W && (*(tr + i)).f_type == CMD)
			{
				j = -1;
				while ((*(tr + i)).arg && *((*(tr + i)).arg + (++j)))
					free(*((*(tr + i)).arg + j));
				free((*(tr + i)).arg);
			}
			if ((*(tr + i)).type == DL && (*(tr + i + 1)).type == W
				&& (*(tr + i)).word)
			{
				unlink((*(tr + i)).word);
				free((*(tr + i)).word);
			}
		}
	}
}

void	dll_child(char **str, t_leaf **tr)
{
	if (str)
	{
		if (*str)
			free(*str);
		*str = NULL;
	}
	destroy_arg_child(*tr);
	if (*tr)
		free(*tr);
	return (*tr = NULL, (void)0);
}

void	dll_no_here(char **str, t_leaf **tr)
{
	if (str)
	{
		if (*str)
			free(*str);
		*str = NULL;
	}
	if (*tr)
		free(*tr);
	return (*tr = NULL, (void)0);
}

void	dall(t_lv *va, unsigned long long int *start)
{
	destroy_va(va);
	parser_destroyer(start);
}
