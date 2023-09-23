/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:23 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 13:19:48 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> 
#include <stdio.h> 

#define MATCH 0
#define NOMATCH 1

int	string_search(t_leaf *arg, char *name, int *i, int *j)
{
	while (arg->word[*i] == '*' && *i < arg->len)
		++(*i);
	if (name[*j] != arg->word[*i])
	{
		while (name[*j])
		{
			if (name[*j] == arg->word[*i] && name[*j + 1] != arg->word[*i])
				break ;
			++(*j);
		}
		if (name[*j] != arg->word[*i])
			return (NOMATCH);
	}
	return (MATCH);
}

int	match(t_leaf *arg, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < arg->len)
	{
		if (arg->word[i] == '*')
		{
			if (string_search(arg, name, &i, &j) == NOMATCH)
				return (NOMATCH);
		}
		else
			if (arg->word[i] != name[j])
				return (NOMATCH);
		if (arg->word[i] == 0)
			break ;
		++j;
		++i;
	}
	if (name[j] != 0)
		return (NOMATCH);
	return (MATCH);
}

int	is_a_wildcard(t_leaf *arg)
{
	int	i;

	i = 0;
	while (i < arg->len)
	{
		if (arg->word[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	wildcard(t_leaf *cmd, t_leaf *arg)
{
	DIR				*d;
	struct dirent	*dir;
	int				is_matching;

	if (is_a_wildcard(arg) == 0)
		return (0);
	is_matching = 0;
	d = opendir(".");
	if (!d)
		return (0);
	dir = readdir(d);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			if (match(arg, dir->d_name) == MATCH)
			{
				++is_matching;
				args_to_array_wildcard(cmd, dir->d_name);
			}
		}
		dir = readdir(d);
	}
	closedir(d);
	return (is_matching);
}
