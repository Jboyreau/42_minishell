#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

#define ALLOC 0
#define UNALLOC 1 

void	print_va(t_lv *va)
{
	int	i;

	if (va == NULL)
		return ;
	i = -1;	
	while ((*(va + (++i))).name)
		printf("declare -x %s=\"%s\"\n", (*(va + i)).name, (*(va + i)).content);
}

int main (int argc, char *arg[], char *env[])
{
	static t_lv	*va = NULL;
	t_leaf		tr[500];

	(*tr).type = 0; (*tr).len = 7; (*tr).word = "toto=42";
	(*(tr + 1)).type = 0; (*(tr + 1)).len = 6; (*(tr + 1)).word = "tonton";
	(*(tr + 2)).type = 0; (*(tr + 2)).len = 7; (*(tr + 2)).word = "toto=2A";
	(*(tr + 3)).type = 0; (*(tr + 3)).len = 13; (*(tr + 3)).word = "tonton=Xavier";
//init :
	va = ft_export(va, env, NULL, 0);
	print_va(va);
	printf("\n\n\n");
//add:
	va = ft_export(va, env, (*tr).word, (*tr).len);	
	print_va(va);
	printf("\n\n\n");
	va = ft_export(va, env, (*(tr + 1)).word, (*(tr + 1)).len);
	print_va(va);
	printf("\n\n\n");
//replace:
	va = ft_export(va, env, (*(tr + 2)).word, (*(tr + 2)).len);	
	print_va(va);
	printf("\n\n\n");
	va = ft_export(va, env, (*(tr + 3)).word, (*(tr + 3)).len);
	print_va(va);
	printf("\n\n\n");
	destroy_va(va);
	return (EXIT_SUCCESS);
}
