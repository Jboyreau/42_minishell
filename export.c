/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:08:30 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 17:36:27 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

t_lv	*destroy_va(t_lv *va)
{
	int	i;

	if (va == NULL)
		return (NULL);
	i = 0;
	while ((*(va + i)).name)
	{
		free((*(va + i)).name);
		++i;
	}
	free(va);
	return (NULL);
}

char	allocate_var_name(char *var, char **name, char **content, int len)
{
	int		i;
	int		j;

	*name = malloc(len + 1);
	if (*name == NULL)
		return (FAILURE);
	i = -1;
	j = 0;
	while (*(var + (++i)) != '=' && i < len)
		*(*name + i) = *(var + i);
	*(*name + i) = 0;
	if (i == len)
		return (*content = *name + i, SUCCESS);
	*content = *name + (++i);
	j = 0;
	while (*(var + i + j) && i + j < len)
	{
		*(*content + j) = *(var + i + j);
		++j;
	}
	*(*content + j) = 0;
	return (SUCCESS);
}

char	indentifier_is_valide(char *variable, int i, int l)
{
	while (*(variable + l))
		++l;
	if ((*variable == ' ' || *variable == '\t')
		|| (*variable >= '0' && *variable <= '9'))
	{
		(write(2, "minishell: export: `", 21), write(2, variable, l));
		write(2, "': not a valid identifier\n", 26);
		return (FAILURE);
	}
	while (*(variable + ++i) != '=' && *(variable + i) != '\0')
	{
		if (*(variable + i) != '_')
		{
			if ((*(variable + i) < 'A' || *(variable + i) > 'Z')
				&& (*(variable + i) < 'a' || *(variable + i) > 'z')
				&& (*(variable + i) < '0' || *(variable + i) > '9'))
			{
				write(2, "minishell: export: `", 21);
				write(2, variable, l);
				return (write(2, "': not a valid identifier\n", 26), FAILURE);
			}
		}
	}
	return (SUCCESS);
}

char	ft_export(t_lv **va, char **env, char *variable, int len)
{
	static char	*content;
	static char	*name;

	if (*va != NULL && variable == NULL)
		return (print_va(*va), SUCCESS);
	if (variable != NULL)
	{
		if (*variable == 0)
			return (
				write(2, "minishell: export: `': not a valid identifier\n", 46),
				FAILURE);
		if (indentifier_is_valide(variable, 0, 0) == FAILURE)
			return (FAILURE);
		if (allocate_var_name(variable, &name, &content, len) == FAILURE)
			return (FAILURE);
	}
	return (*va = export_var(*va, name, content, env), SUCCESS);
}
