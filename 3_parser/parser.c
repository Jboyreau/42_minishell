#include "minishell.h"

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
			if (id == PT_)
				return (QUIT);
			else
				return (ascend());
		}
		return (firstof_one());
	}
	return (firstof_all());
}

static char	check_state(t_rs *state, t_loc *array)
{
	if ((*state).size == 0 || (*state).size - 1 == lstate)
		return (ft_alloc(state, array));
}

static char	find_token(char *f_type, char type, rule_elem **rule)
{
	char	ret;

	while (1)
	{
		if (check_state((t_rs *)*rule, (t_loc *)*rule + 1) == FAILURE)
			return (FAILURE);
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
			return (parser_destroyer(prompt), print_error((*(tr + i)).type));
		++i;
	}
	return (parser_destroyer(prompt), SUCCESS);
}
