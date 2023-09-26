/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:35:53 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:51:16 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	firstof(t_r *rule, int type)
{
	int	i;

	i = 2;
	while (*(rule + i) != (t_r)-1)
		++i;
	++i;
	while (*(rule + i) != (t_r)-1)
	{
		if (*(rule + i) == (t_r)type)
			return (type);
		++i;
	}
	return (12);
}

static char	rule_is_last(t_r *rule)
{
	int	i;

	i = 0;
	while (*(rule + i) != (t_r)-1 && *(rule + i) != (t_r)-2)
		++i;
	if (*(rule + i) == (t_r)-1)
		return (SUCCESS);
	return (FAILURE);
}

static char	search_epsilon(t_r *rule)
{
	int	i;

	i = 2;
	while (*(rule + i) != Z && *(rule + i) != (t_r)-1)
		++i;
	if (*(rule + i) == Z)
		return (SUCCESS);
	return (FAILURE);
}

char	firstof_one(t_r **rule, char type, char *f_type, int i)
{
	if (*((*rule) + i) == (t_r)-1 || *((*rule) + i) == (t_r)-2)
	{
		if ((*((t_rs *)(*(*rule)))).id == PT_ &&
		(*((t_rs *)(*(*rule)))).lstate == 0)
			return (QUIT);
		else
			return (ascend(rule));
	}
	if (*((*rule) + i) < Z && *((*rule) + i) == (t_r)type)
		return (stay(rule, type, f_type, i));
	if (*((*rule) + i) > Z)
	{
		if (firstof((t_r *)(*((*rule) + i)), type) == type)
			return (dive(i, rule));
		if (search_epsilon((t_r *)(*((*rule) + i))) == SUCCESS)
		{
			return (++((*((t_loc *)(*((*rule) + 1))
						+ (*((t_rs *)(*(*rule)))).lstate)).index), ASCEND);
		}
	}
	return (QUIT);
}

char	firstof_all(t_r **rule, char typ, char *f_typ)
{
	int		i;
	t_loc	*l;
	int		ls;

	l = (t_loc *)(*((*rule) + 1));
	ls = (*((t_rs *)(**rule))).lstate;
	i = 2;
	while (*((*rule) + i) != (t_r)(-1))
	{
		if (*((*rule) + i) < Z && *((*rule) + i) == (t_r)typ)
			return (((*(l + ls)).index) = i, stay(rule, typ, f_typ, i));
		if (*((*rule) + i) > Z && firstof((t_r *)(*((*rule) + i)), typ) == typ)
			return (((*(l + ls)).index) = i, dive(i, rule));
		if (rule_is_last((*rule) + i) == SUCCESS)
		{
			if (search_epsilon(*rule) == SUCCESS)
				return (ascend(rule));
			return (QUIT);
		}
		while (*((*rule) + i) != (t_r)(-1) && *((*rule) + i) != (t_r)(-2))
			++i;
		if (*((*rule) + i) == (t_r)(-2))
			++i;
	}
	return (0);
}
