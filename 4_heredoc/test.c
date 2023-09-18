#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <unistd.h>

int main(void)
{
	t_leaf tr[30];

	tr[0].type = DL;
	tr[1].type = W; tr[1].word = "lim"; tr[1].len = 3; tr[1].f_type = LIM;
	tr[2].type = PIPE;
	tr[3].type = DL;
	tr[4].type = W; tr[4].word = "lim1"; tr[4].len = 4; tr[4].f_type = LIM;
	tr[5].type = -1;

	if (heredoc(tr) == FAILURE)
		return (1);

	close(tr[0].fdl);
	//unlink(tr[0].word);
	printf("%s\n", tr[0].word);
	free(tr[0].word);

	close(tr[3].fdl);
	//unlink(tr[3].word);
	printf("%s\n", tr[3].word);
	free(tr[3].word);
	return (0);
}
