#include <stdlib.h>
#include "minishell.h"

static void	reset(r *rule)
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
		(*(location +i)).index = 0;
		++i;
	}
	if ((*state).id == PT_)
		(*state).lstate = 0;
	else
		(*state).lstate = -1;
}

static void	reset_state2(rule_elem *pre, rule_elem *suf)
{
	rule_elem	*pre1;
	rule_elem	*suf1;
	rule_elem	*suf2;
	rule_elem	*red;

	pre1 = (void *)(*(pre + 3));
	red = (void *)(*(pre + 2));
	suf1 = (void *)(*(suf + 3));
	suf2 = (void *)(*(suf1 + 2));
	reset(pre1);
	reset(red);
	reset(suf1);
	reset(suf2);
}

static void	reset_state1(rule_elem *p, rule_elem *nl)
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
	reset(p1);
	reset(cmd);
	reset(cmd1);
	reset(cmd2);
	reset(par);
	reset_state2((void *)(*(cmd + 4)), (void *)(*(cmd2 + 2)));
}

void	reset_state(rule_elem *pt)
{
	rule_elem	*tst;
	rule_elem	*p;
	rule_elem	*tst1;
	rule_elem	*tst2;

	tst = (void *)(*(pt + 2));
	p = (void *)(*(tst + 2));
	tst1 = (void *)(*(tst + 3));
	tst2 = (void *)(*(tst1 + 2));
	reset(pt);
	reset(p);
	reset(tst);
	reset(tst1);
	reset(tst2);
	reset_state1(p, (void *)(*(tst2 + 3)));
}
