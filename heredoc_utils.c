/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:06:14 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/23 17:50:11 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

int	ft_readline1(char **line, const char *prompt)
{
	*line = readline(prompt);
	if (*line == NULL)
		return (FAILURE);
	return (SUCCESS);
}

char	cmp_lim_str(char *str, char *word, int len, int i)
{
	if (*word == '"' && *(word + len - 1) == '"')
	{
		while (len > 0 && *word == '"' && *(word + len - 1) == '"')
		{
			++word;
			len -= 2;
		}
	}
	else if (*word == '\'' && *(word + len - 1) == '\'')
	{
		while (len > 0 && *word == '\'' && *(word + len - 1) == '\'')
		{
			++word;
			len -= 2;
		}
	}
	while (i < len)
	{
		if (*(word + i) != *(str + i))
			return (0);
		++i;
	}
	if (*(str + i))
		return (0);
	return (1);
}

void	d_folder(void *folder)
{
	int	i;

	if (folder)
	{
		i = 0;
		while (*((char **)folder + i))
			free(*((char **)folder + (i++)));
		free(folder);
	}
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (*(s + i))
		i++;
	dup = malloc(i + 1);
	if (dup == 0)
		return (0);
	i = -1;
	while (*(s + (++i)))
		*(dup + i) = *(s + i);
	*(dup + i) = 0;
	return (dup);
}

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		++i;
	return (i);
}
