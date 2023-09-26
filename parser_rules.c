/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:45:07 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 20:53:29 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// I/O_Redirection -> < word | > word | << word | >> word
// Suffixe2 -> I/O_Redirection | word
// Suffixe1 -> Suffixe2 Suffixe1 | epsilon
// Suffixe -> word Suffixe1 | I/O_Redirection Suffixe1
// And_or -> Pipeline And_or1

t_r	*init_rules(void)
{
	static t_r	red[] = {0, 0, L, W, -2, R, W, -2, DL, W, -2, DR, W, -1,
		L, R, DL, DR, -1};
	static t_r	suf2[] = {0, 0, -3, -2, W, -1, L, R, DL, DR, W, -1};
	static t_r	suf1[] = {0, 0, -3, -3, -2, Z, -1, L, R, DL, DR, W, -1};
	static t_r	suf[] = {0, 0, W, -3, -2, -3, -3, -1, L, R, DL, DR, W, -1};
	static t_r	tst[] = {0, 0, -3, -3, -1, L, R, DL, DR, W, OP_PAR, -1};

	*(suf2 + 2) = (t_r)red;
	*(suf1 + 2) = (t_r)suf2;
	*(suf1 + 3) = (t_r)suf1;
	*(suf + 3) = (t_r)suf1;
	*(suf + 5) = (t_r)red;
	*(suf + 6) = (t_r)suf1;
	return (init_id(init1(red, tst, suf)));
}
