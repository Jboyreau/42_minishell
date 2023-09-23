/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:20 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 19:15:42 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// u long long int cfg[cfg_size] = {{tab_size, lstate, id}, tab{prev, index}
//terminals/non_terminals, -2(aka |), -1(aka end), firstof(cfg)}
//Prompt -> And_or Prompt | epsilon

static t_r	*init5(t_r *tst, t_r *par)
{
	static t_r	pt[] = {0, 0, -3, -3, -2, NL, -2, CLS_PAR,
		-1, OP_PAR, W, CLS_PAR, NL, L, R, DL, DR, -1};

	*(pt + 2) = (t_r)tst;
	*(pt + 3) = (t_r)pt;
	*(par + 3) = (t_r)pt;
	return (pt);
}

//And_or2 -> || New_line Pipeline | && New_line Pipeline
//And_or1 -> And_or2 And_or1 | epsilon

static t_r	*init4(t_r *nl, t_r *p,
	t_r *tst, t_r *par)
{
	static t_r	tst2[] = {0, 0, OR, -3, -3, -2, AND, -3, -3, -1, OR, AND, -1};
	static t_r	tst1[] = {0, 0, -3, -3, -2, Z, -1, OR, AND, -1};

	*(tst2 + 3) = (t_r)nl;
	*(tst2 + 4) = (t_r)p;
	*(tst2 + 7) = (t_r)nl;
	*(tst2 + 8) = (t_r)p;
	*(tst1 + 2) = (t_r)tst2;
	*(tst1 + 3) = (t_r)tst1;
	*(tst + 2) = (t_r)p;
	*(tst + 3) = (t_r)tst1;
	return (init5(tst, par));
}
//Pipeline1 -> pipe New_line Cmd Pipeline1 | epsilon
//Pipeline -> Cmd Pipeline1
//New_line -> \n New_line | epsilon

static t_r	*init3(t_r *cmd, t_r *tst, t_r *par)
{
	static t_r	p1[] = {0, 0, PIPE, -3, -3, -3, -2, Z, -1, PIPE, -1};
	static t_r	p[] = {0, 0, -3, -3, -1, OP_PAR, L, R, DL, DR, W, -1};
	static t_r	nl[] = {0, 0, NL, -3, -2, Z, -1, NL, -1};

	*(p1 + 3) = (t_r)nl;
	*(p1 + 4) = (t_r)cmd;
	*(p1 + 5) = (t_r)p1;
	*(p + 2) = (t_r)cmd;
	*(p + 3) = (t_r)p1;
	*(nl + 3) = (t_r)nl;
	return (init4(nl, p, tst, par));
}

//Cmd2 -> Suffixe | epsilon
//Cmd1 -> word Cmd2 | epsilon
//Cmd -> Parentheses | Prefixe Cmd1 | word Cmd2

static t_r	*init2(t_r *suf, t_r *par, t_r *pre, t_r *tst)
{
	static t_r	cmd2[] = {0, 0, -3, -2, Z, -1, L, R, DL, DR, W, -1};
	static t_r	cmd1[] = {0, 0, W, -3, -2, Z, -1, W, -1};	
	static t_r	cmd[] = {0, 0, -3, -2, -3, -3, -2, W, -3, -1,
		OP_PAR, L, R, DL, DR, W, -1};

	*(cmd2 + 2) = (t_r)suf;
	*(cmd1 + 3) = (t_r)cmd2;
	*(cmd + 2) = (t_r)par;
	*(cmd + 4) = (t_r)pre;
	*(cmd + 5) = (t_r)cmd1;
	*(cmd + 8) = (t_r)cmd2;
	return (init3(cmd, tst, par));
}

//Prefixe1 -> I/O_Redirection Prefixe1 | epsilon
//Prefixe -> I/O_Redirection Prefixe1
//Parentheses -> ( Test )

t_r	*init1(t_r *red, t_r *tst, t_r *suf)
{
	static t_r	pre1[] = {0, 0, -3, -3, -2, Z, -1, L, R, DL, DR, -1};
	static t_r	pre[] = {0, 0, -3, -3, -1, L, R, DL, DR, -1};
	static t_r	par[] = {0, 0, OP_PAR, -3, -1, OP_PAR, -1};

	*(pre1 + 2) = (t_r)red;
	*(pre1 + 3) = (t_r)pre1;
	*(pre + 2) = (t_r)red;
	*(pre + 3) = (t_r)pre1;
	return (init2(suf, par, pre, tst));
}
