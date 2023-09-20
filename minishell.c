/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:41 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:56 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include "minishell.h"

void	dall(t_lv *va, r *start)
{
	destroy_va(va);
	parser_destroyer(start);
}

void	dll(char **str, t_leaf **tr) //CRITICAL, DON'T TOUCH.
{
	if (str)
	{
		if (*str)
			free(*str);
		*str = NULL;
	}
	destroy_arg(*tr);
	if (*tr)
		free(*tr);
	return (*tr = NULL, (void)0);
}

static int	ft_readline(char **line, const char *prompt)
{
	*line = readline(prompt);
	if (*line == NULL)
		return (FAILURE);
	if (*line)
		if (**line)
			add_history(*line);
	return (SUCCESS);
}

static char	check_nl(t_cmd *hll, char type, int i, int j)
{
	while ((type > OP_PAR && type < Z) || type == NL)
	{
		(dll(NULL, &(*hll).tr), (*hll).str1 = (*hll).str);
		if (ft_readline(&((*hll).str2), "> ") == FAILURE)
			return (MEM_FAIL);
		(*hll).len = -1;
		while (*((*hll).str1 + (++(*hll).len)))
			(*hll).len1 = -1;
		while (*((*hll).str2 + (++(*hll).len1)))
			++(*hll).len;
		(*hll).str = malloc((*hll).len + 2);
		i = -1;
		while (*((*hll).str1 + (++i)) && (*hll).str)
			*((*hll).str + i) = *((*hll).str1 + i);
		if ((*hll).str)
			*((*hll).str + i++) = '\n';
		j = -1;
		while (i + (++j) < (*hll).len + 2 && (*hll).str)
			*((*hll).str + i + j) = *((*hll).str2 + j);
		(*hll).ret = parser(lexer(hll), (*hll).start);
		if (free((*hll).str2), (*hll).ret)
			return ((*hll).ret);
		(free((*hll).str1), type = (*((*hll).tr + (*hll).count - 3)).type);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	static t_cmd	hll = {.str = NULL, .tr = NULL, .va = NULL};

	(signal(SIGINT, sigint_handler), signal(SIGQUIT, SIG_IGN));
	ft_export(&hll.va, env, NULL, 0);
	hll.start = init_rules();
	while (1)
	{
		if (ft_readline(&(hll.str), "minishell_user: ") == FAILURE)
			return (write(2, "exit\n", 5), dall(hll.va, hll.start), EXIT_FAILURE);
		hll.ret = parser(lexer(&hll), hll.start);
		if (hll.ret == SUCCESS)
		{
			hll.ret = check_nl(&hll, (*(hll.tr + hll.count - 3)).type, 0, 0);
			if (hll.ret == MEM_FAIL)
				return (dll(&(hll.str), &(hll.tr)), dall(hll.va, hll.start), 1);
			if (hll.ret == SUCCESS)
				(heredoc(hll.tr), clean_prompt(&hll.tr), execute(&hll, hll.tr, env));
		}
		else if (hll.ret == MEM_FAIL)
			return (dll(&(hll.str), &(hll.tr)), dall(hll.va, hll.start), 1);
		dll(&(hll.str), &(hll.tr));
	}
	return (dall(hll.va, hll.start), EXIT_SUCCESS);
}
