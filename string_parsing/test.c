#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

#define ALLOC 0
#define UNALLOC 1 

int main (void)
{
	t_leaf	tr[500];
	char	alloc;

	tr[0] = {.type = 0, .len = , .word = "toto\"titi\"\n"};	
	tr[1] = {.type = 0, .len = , .word = "toto\"titi\"\n"};
	tr[2] = {.type = 0, .len = , .word = "toto$var\n"};
	tr[3] = {.type = 0, .len = , .word = "$var\n"};
	tr[4] = {.type = 0, .len = , .word = "*.c\n"};

	for (int i = 0; i < 5; ++i)
	{
		alloc = parse_string(tr + i);
		if ((*(tr + i)).word == NULL)
			return (EXIT_FAILURE);
		printf("%s", (*(tr + i)).word);
		if (alloc == ALLOC)
			free(str);
	}
	return (EXIT_SUCCESS);
}
