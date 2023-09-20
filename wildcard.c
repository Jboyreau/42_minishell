/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:44:23 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/19 15:44:24 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h> 
#include <stdio.h> 

#define MATCH 0
#define NOMATCH 1

/*
opendir
readdir
closedir

Il faut ignorer les fichiers caches et . et ..

*.c
*.*
******.c
a*.c
*a.c

*i*d*r* -> ok
*i*d*l->pas ok
wildcard

Gere les files comme '*file'
Gerer le cas :
*card*toto -> wildcard ne match pas
*/

int string_search(char *pattern, char *name, int *i, int *j)
{
	while (pattern[*i] == '*')
		++(*i);
	if (name[*j] != pattern[*i])
	{
		while (name[*j] && name[*j] != pattern[*i])
			++(*j);
		if (name[*j] != pattern[*i])
			return (NOMATCH);
	}
	return (MATCH);
}

int	match(char *pattern, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			if (string_search(pattern, name, &i, &j) == NOMATCH)
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

int	wildcard(char *pattern)
{
	DIR	*d;
	struct dirent *dir;

	d = opendir(".");
	if (d) {
		dir = readdir(d);
		while (dir != NULL) {
			if (dir->d_name[0] != '.')
				if (match(pattern, dir->d_name) == MATCH)
					//do stuff
			dir = readdir(d);
		}
		closedir(d);
	}
	return (0);
}

// int	main(void)
// {
// 	//wildcard(pattern);
// 	char	*patt[30];
// 	char	*name[30];
// 	char 	*exp[30];

// 	patt[0] = "*a";
// 	name[0] = "abcd";
// 	exp[0] = "NO MATCH";

// 	patt[1] = "a*";
// 	name[1] = "abcd";
// 	exp[1] = "MATCH";

// 	patt[2] = "*a*";
// 	name[2] = "abcd";
// 	exp[2] = "MATCH";

// 	patt[3] = "*a*c*";
// 	name[3] = "abcd";
// 	exp[3] = "MATCH";

// 	patt[4] = "*.c";
// 	name[4] = "file.c";
// 	exp[4] = "MATCH";

// 	patt[5] = "*.c";
// 	name[5] = "file";
// 	exp[5] = "NO MATCH";

// 	patt[6] = "*.*";
// 	name[6] = "file.c";
// 	exp[6] = "MATCH";

// 	patt[7] = "*.*";
// 	name[7] = "file";
// 	exp[7] = "NO MATCH";

// 	patt[8] = "*a*c*z";
// 	name[8] = "abcd";
// 	exp[8] = "NO MATCH";

// 	patt[9] = "toto*a";
// 	name[9] = "toto";
// 	exp[9] = "NO MATCH";

// 	patt[10] = "toto*";
// 	name[10] = "toto";
// 	exp[10] = "MATCH";

// 	patt[11] = "toto*o";
// 	name[11] = "totoo";
// 	exp[11] = "MATCH";

// 	patt[12] = "a";
// 	name[12] = "a";
// 	exp[12] = "MATCH";

// 	patt[13] = "c*****u****_*****";
// 	name[13] = "coucou_ca_va";
// 	exp[13] = "MATCH";

// 	patt[14] = "c*****u****_";
// 	name[14] = "coucou_ca_va";
// 	exp[14] = "NO MATCH";
	
// 	patt[15] = "*******";
// 	name[15] = "toto";
// 	exp[15] = "MATCH";

// 	patt[16] = "*es*";
// 	name[16] = "test";
// 	exp[16] = "MATCH";

// 	patt[17] = "test.*";
// 	name[17] = "test.txt";
// 	exp[17] = "MATCH";
	
	
// 	for (int i = 0; i < 18; i++)
// 	{
// 		printf("----------------TEST %d----------------\n\n", i);
// 		printf("Pattern : %s\nFile : %s\n", patt[i], name[i]);
// 		printf("Expect : %s\n", exp[i]);
// 		printf(match(patt[i], name[i]) == MATCH ? "Result : MATCH\n" : "Result : NO MATCH\n");
// 		printf("\n");
// 	}
// 	return 0;
// }