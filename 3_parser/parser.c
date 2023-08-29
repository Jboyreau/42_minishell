#include "minishell.h"

static void	check_value(r **rule)
{
	t_loc	*loc;

	loc = ((t_loc *)*(*rule + 1)) + (*((t_rs *)(*rule))).lstate;
	if ((*((t_rs *)(*rule))).lstate == 0)
		//choose_production()
	if (*((*rule) + (*loc).index) > 11)
	{
		*rule = (r *)(*((*rule) + (*loc).index));
		++((*loc).index);
	}
	else
}
static void	check_state(r *rule)
{
	if ((*((t_rs *)rule)).size == 0)
		ft_alloc(rule);
	if ((*((t_rs *)rule)).size - 1 <= (*((t_rs *)rule)).lstate)
		ft_realloc(rule);
}

static char	find_token(char *f_type, char type, rule_elem **rule)
{
	while (1)
	{
		check_state(*rule);
		check_value(rule, type, f_type);
	}
	return (SUCCESS);
}

char	parser(t_leaf *tr, rule_elem *rule)
{
	int	i;

	i = 0;
	while ((*(tr + i)).type != -1)
	{
		if (find_token(&(*(tr + i)).f_type, (*(tr + i)).type, &rule) == FAILURE)
			return (parser_destroyer(prompt), print_error((*(tr + i)).type));
		++i;
	}
	return (parser_destroyer(prompt), SUCCESS);
}
