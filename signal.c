/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:19 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/24 19:48:56 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	sigint_handler(int sig)
{
	static int	child;
	static int	heredoc;

	if (heredoc == 1 && sig == SIGINT)
		(close (STDIN_FILENO), write(2, "\n", 1), heredoc = 2, g_signal = 130);
	else if (child == 0 && sig == SIGINT)
	{
		(rl_on_new_line(), rl_replace_line("", 0));
		if (heredoc != 2)
			write(2, "\n", 1);
		(rl_redisplay(), g_signal = 130);
	}
	else if (child == 1)
		signal(SIGINT, SIG_DFL);
	else if (sig == -5)
		heredoc = 1;
	else if (sig == -4)
		child = 2;
	else if (sig == -3)
	{
		child = 0;
		heredoc = 0;
	}
	else if (sig == -2)
		child = 1;
}

void	sigquit_handler(int sig)
{
	static int	child;

	if (sig == -2)
	{
		signal(SIGQUIT, SIG_DFL);
		child = 1;
		return ;
	}
	if (child == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
}
