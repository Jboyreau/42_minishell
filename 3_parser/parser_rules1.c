#include "minishell.h"

// unsigned long long int cfg[cfg_size] = {tab{prev, index}, tab_size, terminals/non_terminals, -2(aka |), -1(aka end)}

static rule_elem	*init5(rule_elem *tst)
{	
	static	rule_elem pt[7] = {0, 0, -3, -3, -2, Z, -1};	//Prompt -> And_or Prompt | epsilon

	*(pt + 2) = (rule_elem)tst;
	*(pt + 3) = (rule_elem)pt;
	return (pt);
}

static rule_elem	*init4(rule_elem *nl, rule_elem *p, rule_elem *tst)
{
	static	rule_elem tst2[10] = {0, 0, OR, -3, -3, -2, AND, -3, -3, -1};	//And_or2 -> || New_line Pipeline | && New_line Pipeline
	static	rule_elem tst1[7] = {0, 0, -3, -3, -2, Z, -1};					//And_or1 -> And_or2 And_or1 | epsilon

	*(tst2 + 3) = (rule_elem)nl;
	*(tst2 + 4) = (rule_elem)p;
	*(tst2 + 7) = (rule_elem)nl;
	*(tst2 + 8) = (rule_elem)p;
	*(tst1 + 2) = (rule_elem)tst2;
	*(tst1 + 3) = (rule_elem)tst1;
	*(tst + 2) = (rule_elem)p;
	*(tst + 3) = (rule_elem)tst1;
	return (init5(tst));
}

static rule_elem	*init3(rule_elem *cmd, rule_elem *tst)
{
	static	rule_elem p1[9] = {0, 0, PIPE, -3, -3, -3, -2, Z, -1};	//Pipeline1 -> pipe New_line Cmd Pipeline1 | epsilon
	static	rule_elem p[5] = {0, 0, -3, -3, -1};					//Pipeline -> Cmd Pipeline1
	static	rule_elem nl[7] = {0, 0, NL, -3, -2, Z, -1};			//New_line -> \n New_line | epsilon

	*(p1 + 3) = (rule_elem)nl;
	*(p1 + 4) = (rule_elem)cmd;
	*(p1 + 5) = (rule_elem)p1;
	*(p + 2) = (rule_elem)cmd;
	*(p + 3) = (rule_elem)p1;
	*(nl + 3) = (rule_elem)nl;
	return (init4(nl, p, tst));
}

static rule_elem	*init2(rule_elem *suf rule_elem *par, rule_elem *pre, rule_elem *tst)
{
	static	rule_elem cmd2[6] = {0, 0, -3, -2, Z, -1};					//Cmd2 -> Suffixe | epsilon
	static	rule_elem cmd1[7] = {0, 0, W, -3, -2, Z, -1};				//Cmd1 -> word Cmd2 | epsilon
	static	rule_elem cmd[10] = {0, 0, -3, -2, -3, -3, -2, W, -3, -1};	//Cmd -> Parentheses | Prefixe Cmd1 | word Cmd2

	*(cmd2 + 2) = (rule_elem)suf;
	*(cmd1 + 3) = (rule_elem)cmd2;
	*(cmd + 2) = (rule_elem)par;
	*(cmd + 4) = (rule_elem)pre;
	*(cmd + 5) = (rule_elem)cmd1;
	*(cmd + 8) = (rule_elem)cmd2;
	return (init3(cmd, tst));
}

rule_elem	*init1(rule_elem *red, rule_elem *pre1, rule_elem *tst, rule_elem *suf)
{
	static	rule_elem pre1[7] = {0, 0, -3, -3, -2, Z, -1};		//Prefixe1 -> I/O_Redirection Prefixe1 | epsilon
	static	rule_elem pre[5] = {0, 0, -3, -3, -1};				//Prefixe -> I/O_Redirection Prefixe1
	static	rule_elem par[6] = {0, 0, OP_PAR, -3, CLS_PAR, -1};	//Parentheses -> ( Test )
	static	rule_elem tst[6] = {0, 0, -3, -3, -1};				//Test -> Pipeline Test1

	*(pre1 + 2) = (rule_elem)red;
	*(pre1 + 3) = (rule_elem)pre1;
	*(pre + 2) = (rule_elem)red;
	*(pre + 3) = (rule_elem)pre1;
	*(par + 3) = (rule_elem)tst;
	return (init2(suf, par, pre, tst));
}
