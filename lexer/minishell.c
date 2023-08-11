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

//	while (hll.str != NULL)
//	{
//		if (ft_readline(&(hll.str), "minishell_user:") == FAILURE)
//			return (EXIT_FAILURE);
		/*Test lexer*/
//		lexer(&hll);
		/*
		int i = 0;
		while ((*(hll.tr + i)).word)
		{
			printf((*(hll.tr + i)).word);
			++i;
		}
		*/
		/*if (parser(lexer(&hll)))
			tree_execution(hll.tr);
		else
			return (EXIT_FAILURE);

			lexical_analysis(high level language) -> tokens, aka hll.tr unbranched.
			syntaxe_analysis(tokens) -> parsed tree, aka hll.tr branched.
			sementic_analysis(parsed tree) -> failure or success
		*/
//		printf("\tbuffer : %s, %p\n", hll.str, hll.str);
//		if (hll.str)
//			free(hll.str);
//		if (hll.tr)
//			free(hll.tr);
//	}
char *str[500];
int	i = 0;
str[0] = "salut\n";
str[1] = "salut<<\n";
str[2] = "salut >>\n";
str[3] = "salut\"toto\"\n";
str[4] = "salut\'to\'to\'\n";
str[5] = "salut    \"to\"    to\"\n";
str[6] = "salut \'toto\'\n";
str[7] = "ls|cat|rev|rev>salut.txt\n";
str[8] = "ls -la| cat -A| rev | rev >> salut.txt \n";
str[9] = "((ls | cat)&&(rev|cat))||ls      > salut\n";
str[10] = "\"Salut\n";

	while (i < 11)
	{
		printf("Prompt : %s", str[i]);
		hll.str = str[i];
		lexer(&hll);
		if (hll.tr)
			free(hll.tr);
		++i;
	}
	return (EXIT_SUCCESS);
}
