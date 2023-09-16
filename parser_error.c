/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:46:46 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 17:47:41 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static char	print_error1(int type, char * word, int len)
{
	if (type == DL)
		return (write(2, "<<'\n", 4), FAILURE);
	if (type == DR)
		return (write(2, ">>'\n", 4), FAILURE);
	if (type == AND)
		return (write(2, "&&'\n", 4), FAILURE);
	if (type == OR)
		return (write(2, "||'\n", 4), FAILURE);
	if (type == W)
		return (write(2, word, len), write(2, "'\n", 2), FAILURE);
	return (FAILURE);
}

char	print_error(int type, char *word, int len)
{
	static char	tokens[] = "0)0<>00(|000";

	write(2, "minishell: syntax error near unexpected token `", 47);
	if (*(tokens + type) != '0')
	{
		write(2, tokens + type, 1);
		return (write(2, "'\n", 2), FAILURE);
	}
	if (type == NL)
		return (write(2, "newline'\n", 9), FAILURE);
	return (print_error1(type, word, len));
}
