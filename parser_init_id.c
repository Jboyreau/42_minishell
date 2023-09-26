/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:11 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:53:12 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_id3(t_r *pre, t_r *suf, t_r *nl)
{
	static t_rs	nl_state = {.size = 0, .lstate = -1, .id = NL_};	
	static t_rs	pre_state = {.size = 0, .lstate = -1, .id = PRE_};
	static t_rs	suf_state = {.size = 0, .lstate = -1, .id = SUF_};

	*nl = (t_r)(&nl_state);
	*pre = (t_r)(&pre_state);
	*suf = (t_r)(&suf_state);
}

static void	init_id2(t_r *pre, t_r *suf, t_r *nl)
{	
	static t_rs	pre1_state = {.size = 0, .lstate = -1, .id = PRE1_};
	static t_rs	red_state = {.size = 0, .lstate = -1, .id = RED_};
	static t_rs	suf1_state = {.size = 0, .lstate = -1, .id = SUF1_};
	static t_rs	suf2_state = {.size = 0, .lstate = -1, .id = SUF2_};

	*((t_r *)(*(pre + 3))) = (t_r)(&pre1_state);
	*((t_r *)(*(pre + 2))) = (t_r)(&red_state);
	*((t_r *)(*(suf + 3))) = (t_r)(&suf1_state);
	*((t_r *)(*(((t_r *)(*(suf + 3))) + 2))) = (t_r)(&suf2_state);
	init_id3(pre, suf, nl);
}

static void	init_id1(t_r *p, t_r *nl)
{
	static t_rs	p1_state = {.size = 0, .lstate = -1, .id = P1_};
	static t_rs	cmd_state = {.size = 0, .lstate = -1, .id = CMD_};
	static t_rs	cmd1_state = {.size = 0, .lstate = -1, .id = CMD1_};
	static t_rs	cmd2_state = {.size = 0, .lstate = -1, .id = CMD2_};
	static t_rs	par_state = {.size = 0, .lstate = -1, .id = PAR_};

	*((t_r *)(*(p + 3))) = (t_r)(&p1_state);
	*((t_r *)(*(p + 2))) = (t_r)(&cmd_state);
	*((t_r *)(*(((t_r *)(*(p + 2))) + 5))) = (t_r)(&cmd1_state);
	*((t_r *)(*(((t_r *)(*(p + 2))) + 8))) = (t_r)(&cmd2_state);
	*((t_r *)(*(((t_r *)(*(p + 2))) + 2))) = (t_r)(&par_state);
	init_id2((t_r *)(*(((t_r *)(*(p + 2))) + 4)),
		(t_r *)(*(((t_r *)(*(((t_r *)(*(p + 2))) + 8))) + 2)), nl);
}

t_r	*init_id(t_r *prompt)
{
	static t_rs	pt_state = {.size = 0, .lstate = 0, .id = PT_};
	static t_rs	tst_state = {.size = 0, .lstate = -1, .id = TST_};
	static t_rs	p_state = {.size = 0, .lstate = -1, .id = P_};
	static t_rs	tst1_state = {.size = 0, .lstate = -1, .id = TST1_};
	static t_rs	tst2_state = {.size = 0, .lstate = -1, .id = TST2_};

	*prompt = (t_r)(&pt_state);
	*((t_r *)(*(prompt + 2))) = (t_r)(&tst_state);
	*((t_r *)(*(((t_r *)(*(prompt + 2))) + 2))) = (t_r)(&p_state);
	*((t_r *)(*(((t_r *)(*(prompt + 2))) + 3))) = (t_r)(&tst1_state);
	*((t_r *)(*(((t_r *)
						(*(((t_r *)
									(*(prompt + 2))) + 3))) + 2))) = (t_r)
		(&tst2_state);
	return (init_id1((t_r *)(*(((t_r *)(*(prompt + 2))) + 2)),
		(t_r *)(*(((t_r *)(*(((t_r *)
		(*(((t_r *)(*(prompt + 2))) + 3))) + 2))) + 3))),
		prompt);
}
