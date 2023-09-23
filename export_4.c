/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:16:23 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/23 17:17:37 by jboyreau         ###   ########.fr       */
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
