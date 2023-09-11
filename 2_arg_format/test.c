#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static void	destroy_arg(t_leaf *tr)
{
	int	i;
	int j;

	i = -1;
	while ((*(tr + (++i))).type != -1)
		if ((*(tr + i)).f_type == CMD)
		{
			j = -1;
			while (*((*(tr + i)).arg + (++j)))
				free(*((*(tr + i)).arg + j));
			free((*(tr + i)).arg);
		}
}

static void	display_args(t_leaf *tr)
{
	int i;
	int j;

	i = -1;
	while ((*(tr + (++i))).type != -1)
		if ((*(tr + i)).f_type == CMD)
		{
			printf("\tCMD__:\n");
			j = -1;
			while (*((*(tr + i)).arg + (++j)))
				printf("%s\n", *((*(tr + i)).arg + j));
		}
}

int	main(int argc, char **argv, char **env)
{
	t_leaf	tr[500];

	(*tr).type = W; (*tr).len = 3; (*tr).word = "cmd"; (*tr).arg = NULL; (*(tr + 0)).f_type = CMD;
	(*(tr + 1)).type = W; (*(tr + 1)).len = 3; (*(tr + 1)).word = "arg"; (*(tr + 1)).f_type = ARG;
	(*(tr + 2)).type = W; (*(tr + 2)).len = 4; (*(tr + 2)).word = "arg1"; (*(tr + 2)).f_type = ARG;
	(*(tr + 3)).type = W; (*(tr + 3)).len = 4; (*(tr + 3)).word = "arg2"; (*(tr + 3)).f_type = ARG;
	(*(tr + 4)).type = W; (*(tr + 4)).len = 4; (*(tr + 4)).word = "arg3"; (*(tr + 4)).f_type = ARG;
	(*(tr + 5)).type = W; (*(tr + 5)).len = 4; (*(tr + 5)).word = "arg4"; (*(tr + 5)).f_type = ARG;

	(*(tr + 6)).type = W; (*(tr + 6)).len = 4; (*(tr + 6)).word = "cmd1"; (*(tr + 6)).arg = NULL; (*(tr + 6)).f_type = CMD;
	(*(tr + 7)).type = W; (*(tr + 7)).len = 5; (*(tr + 7)).word = "2_arg"; (*(tr + 7)).f_type = ARG;
	(*(tr + 8)).type = W; (*(tr + 8)).len = 6; (*(tr + 8)).word = "2_arg1"; (*(tr + 8)).f_type = ARG;
	(*(tr + 9)).type = W; (*(tr + 9)).len = 6; (*(tr + 9)).word = "2_arg2"; (*(tr + 9)).f_type = ARG;
	(*(tr + 10)).type = W; (*(tr + 10)).len = 6; (*(tr + 10)).word = "2_arg3"; (*(tr + 10)).f_type = ARG;
	(*(tr + 11)).type = W; (*(tr + 11)).len = 6; (*(tr + 11)).word = "2_arg4"; (*(tr + 11)).f_type = ARG;

	(*(tr + 12)).type = -1; (*(tr + 12)).f_type = -1;

	int		i = -1;
	t_leaf	*cmd;

	while ((*(tr + (++i))).type != -1)
	{
		if ((*(tr + i)).f_type == CMD)
		{
			//printf("\tcmd index= %d\n", i);
			cmd = tr + i;
		}
		else if ((*(tr + i)).f_type == ARG)
		{
			//printf("arg index= %d\n", i);
			if (args_to_array(cmd, tr + i, NULL) == FAILURE)
				return (EXIT_FAILURE);
		}
	}

	display_args(tr);
	destroy_arg(tr);
	return (EXIT_SUCCESS);
}
