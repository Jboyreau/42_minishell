#include "minishell.h"

static void init_id3(rule_elem *pre, rule_elem *suf, rule_elem *nl)
{
	static t_rs	nl_state = {.size = 0, .lstate = -1, .id = NL_};	
	static t_rs	pre_state = {.size = 0, .lstate = -1, .id = PRE_};
	static t_rs	suf_state = {.size = 0, .lstate = -1, .id = SUF_};

	*nl = (r)(&nl_state);
	*pre = (r)(&pre_state);
	*suf = (r)(&suf_state);
}

static void	init_id2(rule_elem *pre, rule_elem *suf, rule_elem *nl)
{	
	static t_rs	pre1_state = {.size = 0, .lstate = -1, .id = PRE1_};
	static t_rs	red_state = {.size = 0, .lstate = -1, .id = RED_};
	static t_rs	suf1_state = {.size = 0, .lstate = -1, .id = SUF1_};
	static t_rs	suf2_state = {.size = 0, .lstate = -1, .id = SUF2_};

	*((r *)(*(pre + 3))) = (r)(&pre1_state);
	*((r *)(*(pre + 2))) = (r)(&red_state);
	*((r *)(*(suf + 3))) = (r)(&suf1_state);
	*((r *)(*(((r *)(*(suf + 3))) + 2))) = (r)(&suf2_state);
	init_id3(pre, suf, nl); 
}

static void	init_id1(rule_elem *p, rule_elem *nl)
{
	static t_rs	p1_state = {.size = 0, .lstate = -1, .id = P1_};
	static t_rs	cmd_state = {.size = 0, .lstate = -1, .id = CMD_};
	static t_rs	cmd1_state = {.size = 0, .lstate = -1, .id = CMD1_};
	static t_rs	cmd2_state = {.size = 0, .lstate = -1, .id = CMD2_};
	static t_rs	par_state = {.size = 0, .lstate = -1, .id = PAR_};

	*((r *)(*(p + 3))) = (r)(&p1_state);
	*((r *)(*(p + 2))) = (r)(&cmd_state);
	*((r *)(*(((r *)(*(p + 2))) + 5))) = (r)(&cmd1_state);
	*((r *)(*(((r *)(*(p + 2))) + 8))) = (r)(&cmd2_state);
	*((r *)(*(((r *)(*(p + 2))) + 2))) = (r)(&par_state);
	init_id2((r *)(*(((r *)(*(p + 2))) + 4)),
	(r *)(*(((r *)(*(((r *)(*(p + 2))) + 8))) + 2)), nl);
}

rule_elem	*init_id(rule_elem *prompt)
{
	static t_rs	pt_state = {.size = 0, .lstate = 0, .id = PT_};
	static t_rs	tst_state = {.size = 0, .lstate = -1, .id = TST_};
	static t_rs	p_state = {.size = 0, .lstate = -1, .id = P_};
	static t_rs	tst1_state = {.size = 0, .lstate = -1, .id = TST1_};
	static t_rs	tst2_state = {.size = 0, .lstate = -1, .id = TST2_};
	
	*prompt = (r)&pt_state;
	*((r *)(*(prompt + 2))) = (r)(&tst_state);
	*((r *)(*(((r *)(*(prompt + 2))) + 2))) = (r)(&p_state);
	*((r *)(*(((r *)(*(prompt + 2))) + 3))) = (r)(&tst1_state);
	*((r *)(*(((r *)(*(((r *)(*(prompt + 2))) + 3))) + 2))) = (r)(&tst2_state);
	return (init_id1((r *)(*(((r *)(*(prompt + 2))) + 2)),
	(r *)(*(((r *)(*(((r *)(*(((r *)(*(prompt + 2))) + 3))) + 2))) + 3))),
	prompt);
}
