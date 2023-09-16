/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:48:12 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:48:16 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define EXPORT_LEN 6

void execute_tree(t_leaf *tree, t_lv *va)
{
	int	i;
	int j;
	static char	*str = "export";

	i = -1;
	while ((*(tree + (++i))).type != -1)
	{
		j = -1;
		if ((*(tree + i)).len == EXPORT_LEN)
		{
			if ((*(tree + i)).type == W && (*(tree + i)).f_type == CMD)
			{
				while (++j < (*(tree + i)).len && *(str + j))
					if (*(str + j) != *((*(tree + i)).word + j))
						break ;
				if (*(str + j) == 0)
					print_va(va);
			}
		}
	}
}
