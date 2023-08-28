#include "minishell.h"

char	find_token(char *f_type, char type, rule_elem *promptœ)
{
	
}

char	parser(t_leaf *tr, rule_elem *prompt)
{
	int			i;

	i = 0;
	while ((*(tr + i)).type != -1)
	{
		if (find_token(tr + i, (*(tr + i)).type, prompt) == FAILURE)
			return (parser_destroyer(prompt), print_error((*(tr + i)).type))
		++i;
	}
	return (parser_destroyer(prompt), SUCCESS);
}
