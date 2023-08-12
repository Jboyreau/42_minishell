#include <stdlib.h>

static int word_len(t_lv *lv, char *word)
{
	;
}

static void	quote(t_leaf *node)
{
	char	*new_word;
	int i = 0;

	new_word = malloc(((*node).len - 1));
	i = 0;
	while (i < (*node).len - 2)
	{
		*(new_word + i) = *((*node).word + i + 1);
		++i;
	}
	*(new_word + i) = 0;
	(*node).word = new_word;
}

static void dquote(t_leaf *node)
{

}

static void normal(t_leaf *node)
{

}

void	parse_string(t_leaf *node)
{
	char *word;

	word = (*node).word;
	if (*(word + 0) = '\'' && *(word + (*node).len - 1) == '\'')
		return(quote(node));
	if (*(word + 0) = '\"' && *(word + (*node).len - 1) == '\"')
		return(dquote(node));
	return(normal(node));
}
