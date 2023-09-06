#include "minishell.h"
#include <stdio.h>

char		c(t_leaf *tr, int *last_par_found)
{
	int			i;

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
