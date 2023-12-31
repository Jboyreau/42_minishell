/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destroyer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:45:14 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:52:57 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	parser_destroyer2(t_r *pre, t_r *suf)
{
	t_r	*pre1;
	t_r	*suf1;
	t_r	*suf2;
	t_r	*red;

	pre1 = (void *)(*(pre + 3));
	red = (void *)(*(pre + 2));
	suf1 = (void *)(*(suf + 3));
	suf2 = (void *)(*(suf1 + 2));
	if (*(pre + 1))
		free((void *)(*(pre + 1)));
	if (*(suf + 1))
		free((void *)(*(suf + 1)));
	if (*(pre1 + 1))
		free((void *)(*(pre1 + 1)));
	if (*(suf1 + 1))
		free((void *)(*(suf1 + 1)));
	if (*(suf2 + 1))
		free((void *)(*(suf2 + 1)));
	if (*(red + 1))
		free((void *)(*(red + 1)));
}

static void	parser_destroyer1(t_r *p, t_r *nl)
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
	if (*(p1 + 1))
		free((void *)(*(p1 + 1)));
	if (*(cmd + 1))
		free((void *)(*(cmd + 1)));
	if (*(nl + 1))
		free((void *)(*(nl + 1)));
	if (*(cmd1 + 1))
		free((void *)(*(cmd1 + 1)));
	if (*(cmd2 + 1))
		free((void *)(*(cmd2 + 1)));
	if (*(par + 1))
		free((void *)(*(par + 1)));
	parser_destroyer2((void *)(*(cmd + 4)), (void *)(*(cmd2 + 2)));
}

void	parser_destroyer(t_r *pt)
{
	t_r	*tst;
	t_r	*p;
	t_r	*tst1;
	t_r	*tst2;

	tst = (void *)(*(pt + 2));
	p = (void *)(*(tst + 2));
	tst1 = (void *)(*(tst + 3));
	tst2 = (void *)(*(tst1 + 2));
	if (*(pt + 1))
		free((void *)(*(pt + 1)));
	if (*(tst + 1))
		free((void *)(*(tst + 1)));
	if (*(p + 1))
		free((void *)(*(p + 1)));
	if (*(tst1 + 1))
		free((void *)(*(tst1 + 1)));
	if (*(tst2 + 1))
		free((void *)(*(tst2 + 1)));
	parser_destroyer1(p, (void *)(*(tst2 + 3)));
}
