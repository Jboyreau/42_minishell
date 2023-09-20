/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_sub2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:35 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/19 11:27:35 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

char	string_sub2(char **str, t_lv *va)
{
	int			len;
	t_string	new;

	len = string_len2(*str, va);
	new.cursor = 0;
	new.content = malloc(len + 1);
	if (new.content == NULL)
		return (FAILURE);
	if (len == 0)
		*(new.content) = '\0';
	else
		string_cpy2(str, va, &new);
	free(*str);
	*str = new.content;
	return (SUCCESS);
}
