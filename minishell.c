#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

static void	destroyer(t_cmd hll)
{
	int		i;
	t_leaf	*tr;

	i = -1;
	tr = hll.tr;
	while (++i < hll.count)
	{
		if ((*(tr + i)).type < CLS_PAR)
			free((*(tr + i)).word);
		if ((*(tr + i)).type == CMD)
			free((*(tr + i)).arg);
	}
	if (hll.str)
		free(hll.str);
	if (hll.tr)
		free(hll.tr);
}

int	ft_readline(char **line, const char* prompt)
{
	*line = readline(prompt);
	if (*line)
	{
		if (**line)
			add_history(*line);
		return (SUCCESS);
	}
	if (errno != 0)
		return (perror("readline() failure : "), FAILURE);
}

int	main(int agrc, char *argv, char **en)
{
	static	t_cmd hll = {.str = (char *)1, .tr = NULL};
	static	t_lv *va = NULL;

	va = ft_export(va, env, NULL, 0);
	while (1)
	{
		if (ft_readline(&(hll.str), "minishell_user:") == FAILURE)
			return (EXIT_FAILURE);
		if (parser(lexer(&hll)) == SUCCESS)
			execute_tree(hll.tr);
		else
			return (destroyer(hll), EXIT_FAILURE);
		destroyer(hll);
	}
	destroy_va(va);
	return (EXIT_SUCCESS);
}
