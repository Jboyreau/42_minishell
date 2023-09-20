/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:11 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/20 16:22:07 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	destroy_arg(t_leaf *tr)
{
	int	i;
	int j;

	i = -1;
	if (tr)
	{
		while ((*(tr + (++i))).type != -1)
		{
			if ((*(tr + i)).type == W && (*(tr + i)).f_type == CMD)
			{
				j = -1;
				while ((*(tr + i)).arg && *((*(tr + i)).arg + (++j)))
					free(*((*(tr + i)).arg + j));
				free((*(tr + i)).arg);
			}
			if ((*(tr + i)).type == DL)
			{
				unlink((*(tr + i)).word);
				free((*(tr + i)).word);
			}
		}
	}
}

void	ft_str_array_free(t_str_array *array)
{
	int	i;

	i = 0;
	if (array->size > 0)
	{
		while (i < array->size)
		{
			free(array->ptr[i]);
			i++;
		}
	}
	free(array->ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (0);
	while (*s1)
	{
		str[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2++;
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n && (!ft_strlen(s1) || !ft_strlen(s2)))
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while ((*s1 || *s2) && n > 0)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
