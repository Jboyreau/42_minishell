/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:07:36 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 12:51:38 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>

char	builtin_export(t_lv **va, char **env, t_leaf *cmd)
{
	int	i;

	i = 0;
	while (*((*cmd).arg + (++i)))
	{
		if (ft_export(va, env, *((*cmd).arg + i),
			ft_strlen(*((*cmd).arg + i))) == FAILURE)
			return (FAILURE);
	}
	if (i == 1)
		return (ft_export(va, env, NULL, 0));
	return (SUCCESS);
}
