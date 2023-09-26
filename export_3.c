/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:58 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 22:24:02 by cbessonn         ###   ########.fr       */
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
	{
		if (*((*(va + i)).name) != '?' && *((*(va + i)).name) > -1)
		{
			if (*(*(va + i)).content == '\0')
			{
				if (printf("declare -x %s\n", (*(va + i)).name) == -1)
					return (perror("minishell: export: write error"));
			}
			else
			{
				if (printf("declare -x %s=\"%s\"\n", (*(va + i)).name,
						(*(va + i)).content) == -1)
					return (perror("minishell: export: write error"));
			}
		}
	}
}
