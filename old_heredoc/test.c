#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <unistd.h>

#include <string.h>

int main(void)
{
	t_leaf tr[30];

	tr[0].type = DL;
	tr[1].type = W; tr[1].word = "lim"; tr[1].len = 3; tr[1].f_type = LIM;
	tr[2].type = PIPE;
	tr[3].type = DL;
	tr[4].type = W; tr[4].word = "lim1"; tr[4].len = 4; tr[4].f_type = LIM;
	tr[5].type = -1;


	t_lv v[2];

	v[0].name = malloc(16);
	v[0].content = malloc(16);

	v[0].name = strcpy(v[0].name, "USER");
	v[0].content = strcpy(v[0].content, "cbessonn");
	v[1].name = NULL;

	if (heredoc(tr, v) == FAILURE)
		return (1);

	free(v[0].name);
	free(v[0].content);

	close(tr[0].fdl);
	// unlink(tr[0].word);
	free(tr[0].word);

	close(tr[3].fdl);
	// unlink(tr[3].word);
	free(tr[3].word);
	return (0);
}
