/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:58 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 12:51:18 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdio.h>
#include	"minishell.h"

void	print_va(t_lv *va)
{
	int	i;

	if (va == NULL)
		return ;
	i = -1;
	while ((*(va + (++i))).name)
		if (*((*(va + i)).name) != '?' && *((*(va + i)).name) > -1)
			printf("declare -x %s=\"%s\"\n", (*(va + i)).name,
				(*(va + i)).content);
}
