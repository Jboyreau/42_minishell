#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

#define ALLOC 0
#define UNALLOC 1 

int main (int argc, char *arg[], char *env[])
{
/*	t_leaf	tr[500];

	tr[0] = {.type = 0, .len = , .word = "toto\"$USER\""};	
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

	//export_var(NULL, NULL, NULL, env);
	printf("pointeur = %p, premier membre = %s\n", env, *env);
	return (EXIT_SUCCESS);
}
