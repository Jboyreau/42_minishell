#include <stdlib.h>
#include "minishell.h"

static char	ft_alloc(t_rs *state, t_loc)
{
	return (SUCCESS);
}

static char	check_production(r **rule, char type, char *f_type)
{
	t_loc	*location;
	int		*lstate;

	lstate = &((*((t_rs *)(**rule))).lstate);
	location = (((t_loc *)(*((*rule) + 1))) + lstate);
	if ( (*location).index != 0)
	{
		if (*((*rule) + (*location).index) < 0)
		{
			if ((*((t_rs *)(*(*rule)))).id == PT_)
				return (QUIT);
			else
				return (ascend(ASCEND, rule));
		}
		return (firstof_one(rule, type, f_type, (*location).index));
	}
	return (firstof_all(rule, type, f_type));
}

static char	find_token(char *f_type, char type, rule_elem **rule)
{
	char	ret;
	t_rs	*state;
	t_loc	*location;

	while (1)
	{
		state = (t_rs *)(*(*rule));
		location = (t_loc *)(*((*rule) + 1));
		if ((*state).size == 0 || (*state).size - 1 == (*size).lstate)
			return (ft_alloc_loc(state, location));
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

	i = 0;
	while ((*(tr + i)).type != -1)
	{
		if (find_token(&(*(tr + i)).f_type, (*(tr + i)).type, &rule) == FAILURE)
			return (reset_lstate(prompt), print_error((*(tr + i)).type)); //TODO : reset_lstate_location()
		++i;
	}
	return (reset_lstate(prompt), SUCCESS); //TODO : reset_lstate_location()
}
