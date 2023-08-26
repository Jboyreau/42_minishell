#include "minishell.h"

char	parser(t_leaf *tr, rule_elem *prompt)
{
	int			i;

	i = 0;
	while ((*(tr + i)).type != -1)
	{
		if (find_token(tr + i, prompt) == FAILURE)
			return (print_error((*(tr + i)).type))
		++i;
	}
	return (SUCCESS);
}
