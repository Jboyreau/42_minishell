#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

#define ALLOC 0
#define UNALLOC 1 

void print_va(t_lv *va)
{
	int	i;

	if (va == NULL)
		return ;
	i = 0;	
	while ((*(va + i)).name)
	{
		printf("%s ; ", (*(va + i)).name);
		printf("%s\n", (*(va + i)).content);
		++i;
	}
	printf("\n\n\n");
}

int main (int argc, char *arg[], char *env[])
{
	static t_lv	*va = NULL;
	t_leaf		tr[500];

	(*tr).type = 0; (*tr).len = 7; (*tr).word = "toto=42";
	(*(tr + 1)).type = 0; (*(tr + 1)).len = 6; (*(tr + 1)).word = "tonton";
	(*(tr + 2)).type = 0; (*(tr + 2)).len = 7; (*(tr + 2)).word = "toto=2A";
	(*(tr + 3)).type = 0; (*(tr + 3)).len = 13; (*(tr + 3)).word = "tonton=Xavier";
/*	tr[0] = {.type = 0, .len = , .word = "toto\"$USER\""};	
	tr[1] = {.type = 0, .len = , .word = "toto\'$USER\'"};
	tr[2] = {.type = 0, .len = , .word = "toto$var"};
	tr[3] = {.type = 0, .len = , .word = "$var"};
	tr[4] = {.type = 0, .len = 32, .word = "\'salut $USER\' $USER salut \'test\'"};
	tr[5] = {.type = 0, .len = 32, .word = "\"salut $USER\" $USER salut \"test\""};
	tr[6] = {.type = 0, .len = 32, .word = "\'salut \"$USER $USER\" salut test\'"};
	tr[7] = {.type = 0, .len = 32, .word = "\"salut \'$USER $USER\' salut test\""};
	//tr[n] = {.type = 0, .len = , .word = "*.c\n"};

	for (int i = 0; i < 5; ++i)
	{
		parse_string(tr + i);
		if ((*(tr + i)).word == NULL)
			return (EXIT_FAILURE);
		printf("%s\n", (*(tr + i)).word);
		if (str)
			free(str);
	}*/
//init :
	va = ft_export(va, env, NULL, 0);
	print_va(va);
//add:
	va = ft_export(va, env, (*tr).word, (*tr).len);	
	print_va(va);
	va = ft_export(va, env, (*(tr + 1)).word, (*(tr + 1)).len);
	print_va(va);
//replace:
	va = ft_export(va, env, (*(tr + 2)).word, (*(tr + 2)).len);	
	print_va(va);
	va = ft_export(va, env, (*(tr + 3)).word, (*(tr + 3)).len);
	print_va(va);
	destroy_va(va);
	return (EXIT_SUCCESS);
}
