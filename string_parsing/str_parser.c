
#define ALLOC 0
#define UNALLOC 1

static char	quote(t_leaf *node)
{

}

static char dquote(t_leaf *node)
{
}

static char normal(t_leaf *node)
{
}

char	parse_string(t_leaf *node)
{
	char *word;

	word = (*node).word;
	if (*(word + 0) = '\'' && *(word + (*node).len - 1) == '\'')
		return(quote(node));
	if (*(word + 0) = '\"' && *(word + (*node).len - 1) == '\"')
		return(dquote(node));
	return(normal(node));
}
