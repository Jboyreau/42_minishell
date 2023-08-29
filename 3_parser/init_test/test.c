#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static void print_rule(t_rs *state)
{
	char *tab[] = {"PT", "TST", "TST1", "TST2", "P", "P1", "NL", "CMD", "CMD1", "CMD2", "PAR", "PRE", "PRE1", "SUF", "SUF1", "SUF2", "RED"};
	
	printf("size = %d, lstate = %d, rule_id = %s, ", (*state).size, (*state).lstate, *(tab + (*state).id));
}
	
static void print_term(int term)
{
	char *tab[]= {"W", "CLS_PAR", "NL", "L", "R", "DL", "DR", "OP_PAR", "PIPE", "AND", "OR", "Z"};
	printf("%s, ", *(tab + term));
}

static void display(r *rule)
{
	int i;
	
	putchar('{');
	print_rule((t_rs *)(*rule));
	printf("NULL, ");
	i = 2;
	while (*(rule + i) != -1)
	{
		if (*(rule + i) == -2)
			printf("|, ");
		else if (*(rule + i) < 12)
			print_term(*(rule + i));
		else
			printf("%p, ",(r *)(*(rule + i)));
		++i;
	}
	++i;
	printf("firstof() = [");
	while (*(rule + i) != -1)
	{
		print_term(*(rule + i));
		++i;
	}
	putchar(']');
	printf("}\n");
}

static void	display_rules(r *prompt)
{
	r *tst = (r*)(*(prompt + 2));
	r* tst1 = (r*)(*(tst + 3));
	r* tst2 = (r*)(*(tst1 + 2));
	r* p = (r*)(*(tst + 2));
	r* p1 = (r *)(*(p + 3));
	r* nl = (r*)(*(tst2 + 3));
	r* cmd = (r*)(*(p1 + 4));
	r* cmd1 = (r*)(*(cmd + 5));
	r* cmd2 = (r*)(*(cmd + 8));
	r* par = (r*)(*(cmd + 2));
	r* pre = (r*)(*(cmd + 4));
	r* pre1 = (r*)(*(pre + 3));
	r* suf = (r*)(*(cmd2 + 2));
	r* suf1 = (r*)(*(suf + 3));
	r* suf2 = (r*)(*(suf1 + 2));
	r* red = (r*)(*(pre + 2));

	printf("Rules Adresses:\n");
	printf("prompt = %p\n", prompt);
	printf("tst = %p\n", tst);
	printf("tst1 = %p\n", tst1);
	printf("tst2 = %p\n", tst2);
	printf("p = %p\n", p);
	printf("p1 = %p\n", p1);
	printf("nl = %p\n", nl);
	printf("cmd = %p\n", cmd);
	printf("cmd1 = %p\n", cmd1);
	printf("cmd2 = %p\n", cmd2);
	printf("par = %p\n", par);
	printf("pre = %p\n", pre);
	printf("pre1 = %p\n", pre1);
	printf("suf = %p\n", suf);
	printf("suf1 = %p\n", suf1);
	printf("suf2 = %p\n", suf2);
	printf("red = %p\n", red);

	printf("Rules:\n");
	display( prompt);
	display(tst);
	display(tst1);
	display(tst2);
	display(p);
	display(p1);
	display(nl);
	display(cmd);
	display(cmd1);
	display(cmd2);
	display(par);
	display(pre);
	display(pre1);
	display(suf);
	display(suf1);
	display(suf2);
	display(red);
}

int	main(void)
{
	display_rules(init_rules());
	return (EXIT_SUCCESS);
}
