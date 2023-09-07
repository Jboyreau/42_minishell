#include "minishell.h"
#include <stdio.h>

char	c(t_leaf *tr, int *last_par_found)
{
	int	i;

	if ((*(tr + 1)).type != OP_PAR)
		return (SUCCESS);
	i = *last_par_found + 1;
	while ((*(tr + i)).type != CLS_PAR && (*(tr + i)).type != -1)
		++i;
	if ((*(tr + i)).type == CLS_PAR && (*(tr + i + 1)).type == CLS_PAR)
		return (FAILURE);
	if ((*(tr + i)).type == CLS_PAR)
		*last_par_found = i;
	return (SUCCESS);
}

char	d(t_leaf *tr)
{
	int	i;

	if ((*(tr + 1)).type < L || (*(tr + 1)).type > DR)
		return (FAILURE);
	i = 1;
	while ((*(tr + i)).type > NL && (*(tr + i)).type < OP_PAR)
		i += 2;
	if ((*(tr + i)).type == W)
	{
		print_error((*(tr + i)).type, (*(tr + i)).word, (*(tr + i)).len);
		return (FAILURE);
	}
	return (SUCCESS);
}
