#include "minishell.h"
#include <stdio.h>

char	e(t_leaf *tr)
{
	if ((*tr).type == W && (*(tr + 1)).type == OP_PAR)
	{
		print_error((*(tr + 1)).type, (*(tr + 1)).word, (*(tr + 1)).len);
		return (FAILURE);
	}
	if ((*tr).type == CLS_PAR && (*(tr + 1)).type == W)
	{
		print_error((*(tr + 1)).type, (*(tr + 1)).word, (*(tr + 1)).len);
		return (FAILURE);
	}
	if ((*tr).type == CLS_PAR && (*(tr + 1)).type == OP_PAR)
	{
		print_error((*(tr + 1)).type, (*(tr + 1)).word, (*(tr + 1)).len);
		return (FAILURE);
	}
	return (SUCCESS);
}

char    c(t_leaf *tr)
{
    int i;
    int    count;

    count = 0;
    i = 0;
    while ((*(tr + i)).type != NL)
    {
        if ((*(tr + i)).type == OP_PAR)
            ++count;
        if ((*(tr + i)).type == CLS_PAR)
            --count;
        if (count == 0)
        {
            if ((*(tr + 1)).type == OP_PAR)
                if ((*(tr + i)).type == CLS_PAR)
                    if ((*(tr + i - 1)).type == CLS_PAR)
                        return (FAILURE);
        }
        ++i;
    }
    return (SUCCESS);
}

char	d(t_leaf *tr)
{
	int	i;

	if ((*(tr + 1)).type < L || (*(tr + 1)).type > DR)
		return (SUCCESS);
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
