/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:45:01 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 19:46:53 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#define ALLOC_SIZE 500

static char	ft_alloc_loc2(t_rs *state, t_r *loc)
{
	int		i;
	t_loc	*location;
	t_loc	*new;

	(*state).size <<= 1;
	new = malloc((*state).size * sizeof(t_loc));
	if (new == 0)
		return (MEM_FAIL);
	i = -1;
	location = (t_loc *)(*loc);
	while (++i < ((*state).size >> 1))
	{
		(*(new + i)).index = (*(location + i)).index;
		(*(new + i)).prev = (*(location + i)).prev;
	}
	while (++i < (*state).size)
		(*(new + i)).index = 0;
	*loc = (t_r)new;
	free(location);
	return (SUCCESS);
}

char	ft_alloc_loc(t_rs *state, t_r *loc)
{
	int		i;
	t_loc	*location;

	if ((*state).size == 0)
	{
		(*state).size = ALLOC_SIZE;
		*loc = (t_r)malloc((*state).size * sizeof(t_loc));
		if (*loc == 0)
			return (MEM_FAIL);
		i = -1;
		location = (t_loc *)(*loc);
		while (++i < (*state).size)
			(*(location + i)).index = 0;
		return (SUCCESS);
	}
	return (ft_alloc_loc2(state, loc));
}

static char	check_production(t_r **rule, char type, char *f_type)
{
	t_loc	*location;
	int		lstate;

	lstate = (*((t_rs *)(**rule))).lstate;
	location = (((t_loc *)(*((*rule) + 1))) + lstate);
	if ((*location).index != 0)
		return (firstof_one(rule, type, f_type, (*location).index));
	return (firstof_all(rule, type, f_type));
}

static char	find_token(char *f_type, char type, t_r **rule)
{
	char	ret;
	t_rs	*state;

	while (1)
	{
		state = (t_rs *)(*(*rule));
		if ((*state).size == 0 || (*state).size - 1 == (*state).lstate)
			if (ft_alloc_loc(state, (*rule) + 1) == MEM_FAIL)
				return (MEM_FAIL);
		ret = check_production(rule, type, f_type);
		if (ret == DIVE || ret == ASCEND)
			continue ;
		if (ret == STAY)
			break ;
		if (ret == QUIT)
			return (FAILURE);
		if (ret == MEM_FAIL)
			return (MEM_FAIL);
	}
	return (SUCCESS);
}

char	parser(t_leaf *tr, t_r *rule)
{
	int	i;
	int	ret;
	t_r	*prompt;

	if (tr == NULL)
		return (MEM_FAIL);
	i = -1;
	prompt = rule;
	while ((*(tr + (++i))).type != -1)
	{
		if (e(tr + i) == FAILURE)
			return (FAILURE);
		if ((*(tr + i)).type == CLS_PAR && d(tr + i) == FAILURE)
			return (reset_state(prompt), FAILURE);
		if ((*(tr + i)).type == OP_PAR && c(tr + i) == FAILURE)
			return (reset_state(prompt), print_error(CLS_PAR, 0, 0));
		ret = find_token(&(*(tr + i)).f_type, (*(tr + i)).type, &rule);
		if (ret == FAILURE)
			return (reset_state(prompt),
				print_error((*(tr + i)).type, (*(tr + i)).word,
					(*(tr + i)).len));
		if (ret == MEM_FAIL)
			return (MEM_FAIL);
	}
	return (reset_state(prompt), SUCCESS);
}
