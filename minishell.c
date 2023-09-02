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

static void	destroy_all(t_lv *va, r *start)
{
	destroy_va(va);
	parser_destroyer(start);
}

static void	destroy_hll(t_cmd *hll)
{
	if ((*hll).str)
		free((*hll).str);
	if ((*hll).tr)
		free((*hll).tr);
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

int	main(int agrc, char *argv, char **env)
{
	static	t_cmd	hll = {.str = NULL, .tr = NULL, .va = NULL};

	hll.va = ft_export(hll.va, env, NULL, 0);
	hll.start = init_rules(); 
	while (1)
	{
		if (ft_readline(&(hll.str), "minishell_user: ") == FAILURE)
			return (EXIT_FAILURE);
		hll.ret = parser(lexer(&hll), hll.start);
		if (hll.ret == SUCCESS)
		{
			if ((*(hll.tr + hll.count - 3)).type > OP_PAR && (*(hll.tr + hll.count - 3)).type < Z)
				continue ;
			execute_tree(hll.tr, hll.va);
		}
		else if (hll.ret == MEM_FAIL)
			return (destroy_hll(&hll), destroy_all(hll.va, hll.start), EXIT_FAILURE);
		destroy_hll(&hll);
	}
	return (destroy_all(hll.va, hll.start), EXIT_SUCCESS);
}
