/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:55 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:47:43 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

char	find_name(char *name, t_lv *va, int *l)
{
	int	i;
	int	j;

	i = -1;
	while ((*(va + (++i))).name)
	{
		j = -1;
		while (*((*(va + i)).name + (++j)) && *(name + j))
			if (*((*(va + i)).name + j) != *(name + j))
				break ;
		if (*((*(va + i)).name + j) == 0 && *(name + j) == 0)
			return (*l = i, SUCCESS);
	}
	return (FAILURE);
}
