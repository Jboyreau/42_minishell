#include "minishell.h"

static char action(char ret, int i, r **rule) //TODO:dive, ascend, stay, quit 
{
	if (ret == DIVE)
		return (dive());
	if (ret == ASCEND)
		return (ascend());
	if (ret == STAY)
		return (stay());
	return (quit());
}

char	rule_is_last(r *rule)
{
	int	i;

	i = 0;
	while (*(rule + i) != -1 && *(rule + i) != -2)
		++i;
	if (*(rule + i) == -1)
		return(SUCCESS);
	return (FAILURE);
}

char	search_epsilon(r *rule)
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
	if (*((*rule) + i) < Z && *((*rule) + i) == type)
		return (action(STAY, i, rule));
	if (*((*rule) + i) > Z && firstof((r *)(*((*rule) + i))) == type)
		return (action(DIVE, i, rule));
	if (search_epsilon(*rule) == SUCCESS)
		return (action(ASCEND, i, rule));
	return (action(QUIT, i, rule));
}

char	firstof_all(r **rule, char type, char *f_type)
{
	int		i;

	i = 2;
	while (*((*rule) + i) != -1)
	{
		if (*((*rule) + i) < Z && *((*rule) + i) == type)
				return (action(STAY, i, rule));
		if (*((*rule) + i) > Z && firstof((r *)(*((*rule) + i))) == type)
				return (action(DIVE, i, rule));
		if (rule_is_last((*rule) + i) ==  SUCCESS)
		{
			if (search_epsilon(*rule) == SUCCESS)
				return (action(ASCEND, i, rule));
			return (action(QUIT, i, rule));
		}
		while (*((*rule) + i) != -1 && *((*rule) + i) != -2)
			++i;
		if (*((*rule) + i) == -2)
			++i;
	}
	return (0);
}
