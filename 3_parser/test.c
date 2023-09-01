#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int main (void)
{
	static t_cmd	hll = {.str = (char *)1, .tr = NULL};
	char			*str[10000];
	rule_elem		*start;
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
	str[11] = "cmd <<Limiter\n";
	str[12] = "echo \"toto>\"  |  echo \"toto\"\n";
	str[13] = "echo \'toto $USER\' $USER salut \'test\'\n";
	str[14] = "echo \"'\"'\"'\n";
	str[15] = "cat \"file\"\"file\"\n";
	str[16] = "cat \"file\" \"file\"\n";
	str[17] = "cat \"file\"|\"file\"\n";
	str[18] = "cmd |<| ls\n";
	str[19] = "|\n";
	str[20] = "( | )\n";
	str[21] = "<(cmd|cmd)\n";
	str[22] = "(ls | ls | (ls && (ls || ls) | ls && ls)) && (ls|ls|ls) \n";
	str[23] = ">|\n";
	str[24] = "|>>\n";
	str[25] = ")\n";
	str[26] = "\n";
	str[27] = "< file cmd arg > file arg arg\n";
	str[28] = "cmd |\n";

	start = init_rules();
	while (i < 29)
	{
		printf("\nPrompt : %s", str[i]);
		hll.str = str[i];
		lexer(&hll);
		parser(hll.tr, start);
		if (hll.tr)
			free(hll.tr);
		++i;
	}
	parser_destroyer(start);
	return (EXIT_SUCCESS);
}
