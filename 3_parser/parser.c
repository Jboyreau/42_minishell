#include <stdlib.h>
#include "minishell.h"

static char	ft_alloc_loc(t_rs *state, r *loc)
{
	*loc = (r)malloc(20000 * sizeof(t_loc *));
		if (*loc == 0)
			return (MEM_FAIL);
	(*state).size = 20000;
	return (SUCCESS);
}

static char	check_production(r **rule, char type, char *f_type)
{
	t_loc	*location;
	int		lstate;

	lstate = (*((t_rs *)(**rule))).lstate;
	location = (((t_loc *)(*((*rule) + 1))) + lstate);
	if ((*location).index != 0)
		return (firstof_one(rule, type, f_type, (*location).index));
	return (firstof_all(rule, type, f_type));
}

static char	find_token(char *f_type, char type, rule_elem **rule)
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
	}
	return (SUCCESS);
}

char	parser(t_leaf *tr, rule_elem *rule)
{
	int	i;
	int	ret;
	r	*prompt;

	i = 0;
	prompt = rule;
	while ((*(tr + i)).type != -1)
	{
		ret = find_token(&(*(tr + i)).f_type, (*(tr + i)).type, &rule);
		if (ret == FAILURE)
			return (reset_lstate(prompt), print_error((*(tr + i)).type)); //TODO : reset_lstate_location()
		if (ret == MEM_FAIL)
			return (MEM_FAIL);
		++i;
	}
	return (reset_lstate(prompt), SUCCESS); //TODO : reset_lstate_location()
}
