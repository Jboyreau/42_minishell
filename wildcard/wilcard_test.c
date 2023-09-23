/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:23 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/21 16:24:28 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MATCH 0
#define NOMATCH 1

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*(str + i))
		++i;
	return (i);
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

// totoo
// to*o
int string_search_2(char *pattern, char *name, int *i, int *j)
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
	while (dir != NULL) {
		if (dir->d_name[0] != '.')
			if (match_2(file, dir->d_name) == MATCH)
			{
				fprintf(stderr, "test-------%d\n", *is_matching);
				++(*is_matching);
				if (*is_matching > 1)
					return (save_name);
				save_name = dir->d_name;
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

	is_matching = 0;
	d = opendir(".");
	if (d)
	{
		save_name = browse_dir(d, &is_matching, file);
		closedir(d);
	}
	fprintf(stderr, "debug-------%s\n", save_name);
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

int	main(void)
{
	//wildcard(pattern);
	char	*patt[30];
	char	*name[30];
	char 	*exp[30];

	patt[0] = "*a";
	name[0] = "abcd";
	exp[0] = "NO MATCH";

	patt[1] = "a*";
	name[1] = "abcd";
	exp[1] = "MATCH";

	patt[2] = "*a*";
	name[2] = "abcd";
	exp[2] = "MATCH";

	patt[3] = "*a*c*";
	name[3] = "abcd";
	exp[3] = "MATCH";

	patt[4] = "*.c";
	name[4] = "file.c";
	exp[4] = "MATCH";

	patt[5] = "*.c";
	name[5] = "file";
	exp[5] = "NO MATCH";

	patt[6] = "*.*";
	name[6] = "file.c";
	exp[6] = "MATCH";

	patt[7] = "*.*";
	name[7] = "file";
	exp[7] = "NO MATCH";

	patt[8] = "*a*c*z";
	name[8] = "abcd";
	exp[8] = "NO MATCH";

	patt[9] = "toto*a";
	name[9] = "toto";
	exp[9] = "NO MATCH";

	patt[10] = "toto*";
	name[10] = "toto";
	exp[10] = "MATCH";

	patt[11] = "toto*o";
	name[11] = "totoo";
	exp[11] = "MATCH";

	patt[12] = "a";
	name[12] = "a";
	exp[12] = "MATCH";

	patt[13] = "c*****u****_*****";
	name[13] = "coucou_ca_va";
	exp[13] = "MATCH";

	patt[14] = "c*****u****_";
	name[14] = "coucou_ca_va";
	exp[14] = "NO MATCH";
	
	patt[15] = "*******";
	name[15] = "toto";
	exp[15] = "MATCH";

	patt[16] = "*es*";
	name[16] = "test";
	exp[16] = "MATCH";

	patt[17] = "test.*";
	name[17] = "test.txt";
	exp[17] = "MATCH";
	
	patt[18] = "to*o";
	name[18] = "totoo";
	exp[18] = "MATCH";

	patt[19] = "a*b*c";
	name[19] = "abc";
	exp[19] = "MATCH";
  
  	patt[20] = "a*b*c";
	name[20] = "axbycz";
	exp[20] = "NO MATCH";
  
  	patt[21] = "a*b*c";
	name[21] = "axbc";
	exp[21] = "MATCH";
  
  	patt[22] = "a*b*c";
	name[22] = "abzc";
	exp[22] = "MATCH";

	patt[23] = "*ma*k*e";
	name[23] = "makefile";
	exp[23] = "MATCH";

	for (int i = 0; i < 24; i++)
	{
		printf("----------------TEST %d----------------\n\n", i);
		printf("Pattern : %s\nFile : %s\n", patt[i], name[i]);
		printf("Expect : %s\n", exp[i]);
		printf(match_2(patt[i], name[i]) == MATCH ? "Result : MATCH\n" : "Result : NO MATCH\n");
		printf("\n");
	}
	return 0;
}
