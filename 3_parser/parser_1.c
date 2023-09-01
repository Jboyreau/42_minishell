#include "minishell.h"

static char	firstof(r* rule, int type)
{
	int	i;

	i = 2;
	while (*(rule + i) != -1)
		++i;
	++i;
	while(*(rule + i) != -1)
	{
		if (*(rule + i) == type)
			return (type);
		++i;
	}
	return (12);
}

static char	rule_is_last(r *rule)
{
	int	i;

	i = 0;
	while (*(rule + i) != -1 && *(rule + i) != -2)
		++i;
	if (*(rule + i) == -1)
		return(SUCCESS);
	return (FAILURE);
}

static char	search_epsilon(r *rule)
{
	int	i;

	i = 2;
	while (*(rule + i) != Z && *(rule + i) != -1)
		++i;
	if (*(rule + i) == Z)
		return(SUCCESS);
	return (FAILURE);
}

char	firstof_one(r **rule, char type, char *f_type, int i)
{
	if (*((*rule) + i) < 0)
	{
		if ((*((t_rs *)(*(*rule)))).id == PT_)
			return (STAY);
		else
			return (ascend(rule));
	}
	if (*((*rule) + i) < Z && *((*rule) + i) == type)
		return (stay(rule, type, f_type, i));
	if (*((*rule) + i) > Z && firstof((r *)(*((*rule) + i)), type) == type)
		return (dive(i, rule));
	if (search_epsilon(*rule) == SUCCESS)
		return (ascend(rule));
	return (QUIT);
}

char	firstof_all(r **rule, char type, char *f_type)
{
	int		i;
	t_loc	*l;
	int		ls;

	l = (t_loc *)(*((*rule) + 1));
	ls = (*((t_rs *)(**rule))).lstate;
	i = 2;
	while (*((*rule) + i) != -1)
	{
		if (*((*rule) + i) < Z && *((*rule) + i) == type)
				return (((*(l + ls)).index) = i, stay(rule, type, f_type, i));
		if (*((*rule) + i) > Z && firstof((r *)(*((*rule) + i)), type) == type)
				return (((*(l + ls)).index) = i, dive(i, rule));
		if (rule_is_last((*rule) + i) ==  SUCCESS)
		{
			if (search_epsilon(*rule) == SUCCESS)
				return (ascend(rule));
			return (QUIT);
		}
		while (*((*rule) + i) != -1 && *((*rule) + i) != -2)
			++i;
		if (*((*rule) + i) == -2)
			++i;
	}
	return (0);
}
