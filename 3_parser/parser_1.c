#include <stdlib.h>
#include "minishell.h"

char	firstof_one()
{
	//ret = check (one)
	if (ret == DIVE)
		return (dive());
	if (ret == ASCEND)
		return (ascend());
	if (ret == STAY)	
		return (stay());
	return (quit());
}

char	firstof_all()
{
	//ret = check (all)
	if (ret == DIVE)
		return (dive());
	if (ret == ASCEND)
		return (ascend());
	if (ret == STAY)	
		return (stay());
	return (quit());
}

char	ft_alloc(t_rs *state, t_loc)
{
	return (SUCCESS);
}
