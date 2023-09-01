#include "minishell.h"

char dive(int i, r **rule)
{
	r		*prev;
	t_loc	*loc;
	int		lstate;

	loc = (t_loc *)(*((*rule) + 1));
	lstate = (*((t_rs *)(**rule))).lstate;
	++((*(loc + lstate)).index);
	prev = *rule;
	*rule = (r *)(*((*rule) + i));
	loc = (t_loc *)(*((*rule) + 1));
	++((*((t_rs *)(**rule))).lstate);
	lstate = (*((t_rs *)(**rule))).lstate;
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
		return (STAY);
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
	return (STAY);
}
