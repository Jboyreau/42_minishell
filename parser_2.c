/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:46:06 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:47:41 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

char dive(int i, r **rule)
{
	t_rs	*state;
	r		*prev;
	t_loc	*loc;
	int		lstate;

	loc = (t_loc *)(*((*rule) + 1));
	lstate = (*((t_rs *)(**rule))).lstate;
	((*(loc + lstate)).index) = i + 1;
	prev = *rule;
	*rule = (r *)(*((*rule) + i));
	++((*((t_rs *)(**rule))).lstate);
	lstate = (*((t_rs *)(**rule))).lstate;
	state = (t_rs *)(*(*rule));
	if ((*state).size == 0 || (*state).size - 1 == (*state).lstate)
		if (ft_alloc_loc(state, (*rule) + 1) == MEM_FAIL)
			return (MEM_FAIL);
	loc = (t_loc *)(*((*rule) + 1));
	(*(loc + lstate)).prev = prev;
	return (DIVE);
}

char ascend(r **rule)
{
	int		*save_lstate;
	t_loc	*loc;
	int		lstate;

	loc = (t_loc *)(*((*rule) + 1));
	save_lstate = &((*((t_rs *)(**rule))).lstate);
	lstate = (*((t_rs *)(**rule))).lstate;
	((*(loc + lstate)).index) = 0;
	*rule = (*(loc + lstate)).prev;
	--(*save_lstate);
	return (ASCEND);
}

char stay(r **rule, char type, char *f_type, int i)
{
	t_loc	*loc;
	int		lstate;

	loc = (t_loc *)(*((*rule) + 1));
	lstate = (*((t_rs *)(**rule))).lstate;
	++((*(loc + lstate)).index);
	if (type == W)
	{
		if ((*((t_rs *)(**rule))).id == CMD_)
			return(*f_type = CMD, STAY);
		if ((*((t_rs *)(**rule))).id == CMD1_)
			return(*f_type = CMD, STAY);
		if ((*((t_rs *)(**rule))).id == SUF_)
			return(*f_type = ARG, STAY);
		if ((*((t_rs *)(**rule))).id == SUF2_)
			return(*f_type = ARG, STAY);
		if ((*((t_rs *)(**rule))).id == RED_)
		{
			if (*((*rule) + i - 1) == DL)
				return(*f_type = LIM, STAY);
			return(*f_type = FIL, STAY);
		}
	}
	return (STAY);
}
