#include "minishell.h"

rule_elem	*init_rules()
{
	static	r red[14] = {0, 0, L, W, -2, R, W, -2, DL, W, -2, DR, W, -1,
	L, R, DL, DR, -1};														//I/O_Redirection -> < word | > word | << word | >> word
	static	r suf2[6] = {0, 0, -3, -2, W, -1, L, R, DL, DR, W, -1};			//Suffixe2 -> I/O_Redirection | word
	static	r suf1[7] = {0, 0, -3, -3, -2, Z, -1, L, R, DL, DR, W, -1};		//Suffixe1 -> Suffixe2 Suffixe1 | epsilon
	static	r suf[8] = {0, 0, W, -3, -2, -3, -3, -1, L, R, DL, DR, W, -1};	//Suffixe -> word Suffixe1 | I/O_Redirection Suffixe1
	static	r tst[5] = {0, 0, -3, -3, -1, L, R, DL, DR, W, OP_PAR, -1};		//And_or -> Pipeline And_or1

	*(suf2 + 2) = (rule_elem)red;
	*(suf1 + 2) = (rule_elem)suf2;
	*(suf1 + 3) = (rule_elem)suf1;
	*(suf + 3) = (rule_elem)suf1;
	*(suf + 5) = (rule_elem)red;
	*(suf + 6) = (rule_elem)suf1;
	return (init1(red, pre1, tst, suf));
}
