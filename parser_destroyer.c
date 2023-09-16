/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destroyer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:46:38 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:47:41 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	parser_destroyer2(rule_elem *pre, rule_elem *suf)
{
	rule_elem	*pre1;
	rule_elem	*suf1;
	rule_elem	*suf2;
	rule_elem	*red;

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

static void	parser_destroyer1(rule_elem *p, rule_elem *nl)
{
	rule_elem	*p1;
	rule_elem	*cmd;
	rule_elem	*cmd1;
	rule_elem	*cmd2;
	rule_elem	*par;

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

void	parser_destroyer(rule_elem *pt)
{
	rule_elem	*tst;
	rule_elem	*p;
	rule_elem	*tst1;
	rule_elem	*tst2;

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
