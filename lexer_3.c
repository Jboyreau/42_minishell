#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

char	rev_char_is_token(char c0, char c1, int *j)
{
	char *t;

	t = ")\n(<>|";

	if ((c0 == '<' || c0 == '>' || c0 == '|' || c0 == '&') && (c0 == c1))
			return ((*j) -= 2, SUCCESS);
	while (*t)
	{
		if (c0 == *t)
			return (--(*j), SUCCESS);
		++t;
	}
	return (FAILURE);
}

static void	fnormal_string(t_leaf *tr, char *str, int *i, int *count)
{
	int s;
	int	j;
	int	test;

	s = *i;
	test = 1;
	if (*(str + (*i)) == '$')
	{
		j = *i;
		while (j > -1 && *(str + j) != '$' && *(str + j) != ' ' &&
		rev_char_is_token(*(str + j), *(str + j + 1), &j) == FAILURE)
			--j;
		if (j > 0)
			if ((*str + j) == '$')
				(++(*i), test = 0);
	}
	while (*(str + (*i)))
	{
		if (*(str + (*i)) == ' ' || (*(str + (*i)) == '$' && test == 0))
			return (fill_leaf(tr, W, *i-s, str + s), ++(*count), (void)0);
		if (char_is_token(*(str + (*i)), *(str + (*i) + 1), &j) == SUCCESS)
			return (fill_leaf(tr, W, *i-s, str + s), ++(*count), (void)0);
		++(*i);
	}
	return (fill_leaf(tr, W, *i-s, str + s), ++(*count), (void)0);
}

static void	fdq_sequence(t_leaf *tr, char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\"' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (fnormal_string(tr, str, i, count));
	while (char_is_token(str[j], str[j + 1], &b) == 1 && *(str + j) != ' ')
		++j;
	if (*(str + j) == '\n')
		return (fnormal_string(tr, str, i, count));
	fill_leaf(tr, W, (j - (*i)), str + (*i));
	return (*i = j, ++(*count), (void)0);
}

static void	fq_sequence(t_leaf *tr, char *str, int *i, int *count)
{
	int			j;
	int			b;

	j = *i + 1;
	while (*(str + j) != '\'' && *(str + j))
		++j;
	if (*(str + j) == 0)
		return (fnormal_string(tr, str, i, count));
	while (char_is_token(str[j], str[j + 1], &b) == 1 && *(str + j) != ' ')
		++j;
	if (*(str + j) == '\n')
		return (fnormal_string(tr, str, i, count));
	fill_leaf(tr, W, (j - (*i)), str + (*i));
	return (*i = j, ++(*count), (void)0);
}

void	flongest_token(t_leaf *tr, char *str, int *i, int *count)
{
	if (*(str + (*i)) == '\'')
		return (fq_sequence(tr, str, i, count));
	if (*(str + (*i)) == '\"')
		return (fdq_sequence(tr, str, i, count));
	return (fnormal_string(tr, str, i, count));
}
