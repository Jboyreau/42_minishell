/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:42 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 13:11:03 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_lv *va, char **arg)
{
	int	index;
	int	i;

	i = 0;
	while (*(arg + (++i)))
		if (find_name(*(arg + i), va, &index) == SUCCESS)
			*((*(va + index)).name) = -1;
	return (SUCCESS);
}
