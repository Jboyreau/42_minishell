/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:14 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:53:22 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	reset(t_r *rule)
{
	int		i;
	t_rs	*state;
	t_loc	*location;

	location = (t_loc *)(*(rule + 1));
	if (location == NULL)
		return ;
	state = (t_rs *)(*rule);
	i = 0;
	while (i < (*state).size)
	{
		(*(location + i)).index = 0;
		++i;
	}
	if ((*state).id == PT_)
		(*state).lstate = 0;
	else
		(*state).lstate = -1;
}

static void	reset_state2(t_r *pre, t_r *suf)
{
	t_r	*pre1;
	t_r	*suf1;
	t_r	*suf2;
	t_r	*red;

	pre1 = (void *)(*(pre + 3));
	red = (void *)(*(pre + 2));
	suf1 = (void *)(*(suf + 3));
	suf2 = (void *)(*(suf1 + 2));
	reset(pre1);
	reset(red);
	reset(suf1);
	reset(suf2);
}

static void	reset_state1(t_r *p)
{
	t_r	*p1;
	t_r	*cmd;
	t_r	*cmd1;
	t_r	*cmd2;
	t_r	*par;

	p1 = (void *)(*(p + 3));
	cmd = (void *)(*(p + 2));
	cmd1 = (void *)(*(cmd + 5));
	cmd2 = (void *)(*(cmd + 8));
	par = (void *)(*(cmd + 2));
	reset(p1);
	reset(cmd);
	reset(cmd1);
	reset(cmd2);
	reset(par);
	reset_state2((void *)(*(cmd + 4)), (void *)(*(cmd2 + 2)));
}

void	reset_state(t_r *pt)
{
	t_r	*tst;
	t_r	*p;
	t_r	*tst1;
	t_r	*tst2;

	tst = (void *)(*(pt + 2));
	p = (void *)(*(tst + 2));
	tst1 = (void *)(*(tst + 3));
	tst2 = (void *)(*(tst1 + 2));
	reset(pt);
	reset(p);
	reset(tst);
	reset(tst1);
	reset(tst2);
	reset_state1(p);
}
