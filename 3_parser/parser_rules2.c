#include "minishell.h"

static void init_id3(rule_elem *pre, rule_elem *suf, rule_elem *nl)
{
	static t_rs	nl_state = {.size = 0, .lstate = 0, .id = NL};	
	static t_rs	pre_state = {.size = 0, .lstate = 0, .id = PRE};
	static t_rs	suf_state = {.size = 0, .lstate = 0, .id = SUF};

	*nl = (r)(&nl_state);
	*pre = (r)(&pre_state);
	*suf = (r)(&suf_state);
}

static void	init_id2(rule_elem *pre, rule_elem *suf, rule_elem *nl)
{	
	static t_rs	pre1_state = {.size = 0, .lstate = 0, .id = PRE1};
	static t_rs	red_state = {.size = 0, .lstate = 0, .id = RED};
	static t_rs	suf1_state = {.size = 0, .lstate = 0, .id = SUF1};
	static t_rs	suf2_state = {.size = 0, .lstate = 0, .id = SUF2};

	*((r *)(*(pre + 3))) = (r)(&pre1_state); //pre1
	*((r *)(*(pre + 2))) = (r)(&red_state); //red
	*((r *)(*(suf + 3))) = (r)(&suf1_state); //suf1
	*((r *)(*(suf1 + 2))) = (r)(&suf2_state); //suf2
	init_id3(pre, suf, nl); 
}

static void	init_id1(rule_elem *p, rule_elem *nl)
{
	static t_rs	p1_state = {.size = 0, .lstate = 0, .id = P1};
	static t_rs	cmd_state = {.size = 0, .lstate = 0, .id = CMD};
	static t_rs	cmd1_state = {.size = 0, .lstate = 0, .id = CMD1};
	static t_rs	cmd2_state = {.size = 0, .lstate = 0, .id = CMD2};
	static t_rs	par_state = {.size = 0, .lstate = 0, .id = PAR};

	*((r *)(*(p + 3))) = (r)(&p1_state);
	*((r *)(*(p + 2))) = (r)(&cmd_state);
	*((r *)(*(cmd + 5))) = (r)(&cmd1_state);
	*((r *)(*(cmd + 8))) = (r)(&cmd2_state);
	*((r *)(*(cmd + 2))) = (r)(&par_state);
	init_id2((r *)(*(cmd + 4)), (r *)(*(cmd2 + 2)));
}

rule_elem	*init_id(rule_elem *prompt)
{
	static t_rs	pt_state = {.size = 0, .lstate = 0, .id = PT};
	static t_rs	tst_state = {.size = 0, .lstate = 0, .id = TST};
	static t_rs	p_state = {.size = 0, .lstate = 0, .id = P};
	static t_rs	tst1_state = {.size = 0, .lstate = 0, .id = TST1};
	static t_rs	tst2_state = {.size = 0, .lstate = 0, .id = TST2};
	
	*prompt = (r)&pt_state;
	*((r *)(*(prompt + 2))) = (r)(&tst_state);
	*((r *)(*(tst + 2))) = (r)(&p_state);
	*((r *)(*(tst + 3))) = (r)(&tst1_state);
	*((r *)(*(tst1 + 2))) = (r)(&tst2_state);
	return (init_id1((r *)(*(tst + 2)), (r *)(*(tst2 + 3))), prompt);
}
