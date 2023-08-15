#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

static void	ch_type(t_leaf *tr, char *str, int len, int count)
{
	if (count == 0)
		return (fill_leaf(tr, CMD, len, str), (void)0);
	if ((*(tr - 1)).type == CMD || (*(tr - 1)).type == ARG)
		fill_leaf(tr, ARG, len, str);
	else if ((*(tr - 1)).type == R_QUOTE || (*(tr - 1)).type == DR_QUOTE || (*(tr - 1)).type == L_QUOTE)
		fill_leaf(tr, FIL, len, str);
	else if ((*(tr - 1)).type == DL_QUOTE)
		fill_leaf(tr, LIM, len, str);
	else if ((*(tr - 1)).type > NL && (*(tr - 1)).type <= OR)
		fill_leaf(tr, CMD, len, str);
}

static void	fnormal_string(t_leaf *tr, char *str, int *i, int *count)
{
	int s;
	static int bidon;

	s = *i;
	while (*(str + (*i)))
	{
		if (*(str + (*i)) == ' ')
			return (ch_type(tr, str + s, *i-s, *count), ++(*count), (void)0);
		if (char_is_token(*(str + (*i)), *(str + (*i) + 1), &bidon) == SUCCESS)
			return (ch_type(tr, str + s, *i-s, *count), ++(*count), (void)0);
		++(*i);
	}
	return (ch_type(tr, str + s, *i-s, *count), ++(*count), (void)0);
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
	ch_type(tr, str + (*i), (j - (*i)), *count);
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
	ch_type(tr, str + (*i), (j - (*i)), *count);
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
