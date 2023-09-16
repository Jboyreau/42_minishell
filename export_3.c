/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:48:35 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:48:38 by jboyreau         ###   ########.fr       */
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
		printf("declare -x %s=\"%s\"\n", (*(va + i)).name, (*(va + i)).content);
}

