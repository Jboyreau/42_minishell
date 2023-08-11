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

int	main(void)
{
	static t_cmd hll = {.str = (char *)1, .tr = NULL};

	while (hll.str != NULL)
	{
		if (ft_readline(&(hll.str), "minishell_user:") == FAILURE)
			return (EXIT_FAILURE);
		if (parser(lexer(&hll)) == SUCCESS)
			execute_tree(hll.tr);
		else
		{
			if (hll.str)
				free(hll.str);
			if (hll.tr)
				free(hll.tr);
			return (EXIT_FAILURE);
		}
		if (hll.str)
			free(hll.str);
		if (hll.tr)
			free(hll.tr);
	}
	return (EXIT_SUCCESS);
}
