#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

char	ft_alloc_loc(t_rs *state, r *loc) //TODO : final version
{
	int		i;
	t_loc	*location;

	(*state).size = 20000;
	*loc = (r)malloc((*state).size * sizeof(t_loc));
		if (*loc == 0)
			return (MEM_FAIL);
	i = -1;
	location = (t_loc *)(*loc);
	while (++i < (*state).size)
		(*(location + i)).index = 0;
	return (SUCCESS);
}

static char	check_production(r **rule, char type, char *f_type)
{
	t_loc	*location;
	int		lstate;

	lstate = (*((t_rs *)(**rule))).lstate;
	location = (((t_loc *)(*((*rule) + 1))) + lstate);
printf("index = %d, rule = %d, value = %lld \n", (*location).index, (*((t_rs *)(**rule))).id, *((*rule) + (*location).index));
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
			return (reset_state(prompt), print_error((*(tr + i)).type));
		if (ret == MEM_FAIL)
			return (MEM_FAIL);
		++i;
	}
	return (reset_state(prompt), SUCCESS);
}
