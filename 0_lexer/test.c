#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int main (void)
{
	static t_cmd	hll = {.str = (char *)1, .tr = NULL};	
	char			*str[10000];
	int				i = 0;

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
	str[11] = "<<Limiter\n";
	str[12] = "echo \"toto>\"  |  echo \"toto\"\n";
	str[13] = "echo \'toto $USER\' $USER salut \'test\'\n";
	str[14] = "\"'\"'\"'";

	while (i < 15)
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
