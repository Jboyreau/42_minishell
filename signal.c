/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:19 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 16:13:53 by cbessonn         ###   ########.fr       */
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

	if (sig == -4)
	{
		child = 2;
		return ;
	}
	if (sig == -3)
	{
		child = 0;
		return ;
	}
	if (sig == -2)
	{
		child = 1;
		return ;
	}
	if (child == 1)
	{
		signal(SIGINT, SIG_DFL);
		return ;
	}
	if (child == 0 && sig == SIGINT)
	{
		write(2, "\n", 1);
    	rl_replace_line("", 0);
    	rl_on_new_line();
    	rl_redisplay();
		return ;
	}
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
