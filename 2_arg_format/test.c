#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static void	display_args(char **arg)
{
	int i = -1;

	while (*(arg + (++i)))
		printf("%s\n", *(arg + i));
}

int	main(int argc, char **argv, char **env)
{
	t_leaf	tr[500];

	(*tr).type = WORD; (*tr).len = 3; (*tr).word = "cmd"; (*tr).arg = NULL;	
	(*(tr + 1)).type = WORD; (*(tr + 1)).len = 3; (*(tr + 1)).word = "arg";
	(*(tr + 2)).type = WORD; (*(tr + 2)).len = 4; (*(tr + 2)).word = "arg1";
	(*(tr + 3)).type = WORD; (*(tr + 3)).len = 4; (*(tr + 3)).word = "arg2";
	(*(tr + 4)).type = WORD; (*(tr + 4)).len = 4; (*(tr + 4)).word = "arg3";
	(*(tr + 5)).type = WORD; (*(tr + 5)).len = 4; (*(tr + 5)).word = "arg4";
	(*(tr + 6)).word = NULL;

	int i = 0;
	while ((*(tr + (++i))).word)
		if (args_to_array(tr, tr + i) == FAILURE)
			return (EXIT_FAILURE);
	display_args((*tr).arg);
	free((*tr).arg);
	return (EXIT_SUCCESS);
}
