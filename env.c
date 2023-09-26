/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:34:28 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 21:58:13 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	env(t_lv *va)
{
	int	i;

	if (va == NULL)
		return (0);
	i = -1;
	while ((*(va + (++i))).name)
		if (*((*(va + i)).name) != '?' && *((*(va + i)).name)
			> -1 && *(*(va + i)).content != '\0')
			if (printf("%s=%s\n", (*(va + i)).name, (*(va + i)).content) == -1)
				return (perror("minishell: env: write error"), 0);
	return (0);
}
