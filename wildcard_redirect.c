/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:23 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 13:16:16 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MATCH 0
#define NOMATCH 1

int	string_search_2(char *pattern, char *name, int *i, int *j)
{
	while (pattern[*i] == '*')
		++(*i);
	if (name[*j] != pattern[*i])
	{
		while (name[*j])
		{
			if (name[*j] == pattern[*i] && name[*j + 1] != pattern[*i])
				break ;
			++(*j);
		}
		if (name[*j] != pattern[*i])
			return (NOMATCH);
	}
	return (MATCH);
}

int	match_2(char *pattern, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			if (string_search_2(pattern, name, &i, &j) == NOMATCH)
				return (NOMATCH);
		}
		else
			if (pattern[i] != name[j])
				return (NOMATCH);
		if (pattern[i] == 0)
			break ;
		++j;
		++i;
	}
	if (name[j] != 0)
		return (NOMATCH);
	return (MATCH);
}

int	is_a_wildcard_2(char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	*browse_dir(DIR *d, int *is_matching, char *file)
{
	struct dirent	*dir;
	char			*save_name;

	dir = readdir(d);
	save_name = NULL;
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			if (match_2(file, dir->d_name) == MATCH)
			{
				++(*is_matching);
				if (*is_matching > 1)
					return (save_name);
				save_name = dir->d_name;
			}
		}
		dir = readdir(d);
	}
	return (save_name);
}

int	wildcard_redirect(char *file)
{
	DIR				*d;
	int				is_matching;
	char			*save_name;

	if (is_a_wildcard_2(file) == 0)
		return (0);
	is_matching = 0;
	d = opendir(".");
	if (d)
	{
		save_name = browse_dir(d, &is_matching, file);
		closedir(d);
	}
	if (is_matching == 1)
		return (free(file), file = ft_strdup(save_name), 1);
	else if (is_matching > 1)
	{
		write(2, "bash: ", 6);
		write(2, file, ft_strlen(file));
		write(2, ": ambiguous redirect\n", 22);
		return (-1);
	}
	return (0);
}
