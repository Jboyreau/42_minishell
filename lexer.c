#include <stdlib.h>
#include <stdio.h> //debug
#include <unistd.h> //debug
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

void	fill_leaf(t_leaf *tr, char type, int len, char *word)
{
	(*tr).type = type;
	(*tr).len = len;
	(*tr).word = word;
	(*tr).f_type = 0;
	(*tr).fdl = 0;
	(*tr).arg = 0;
}

static void	fill_tree(char *str, t_leaf *tr)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (*(str + i))
	{
		while (*(str + i) == ' ')
			++i;
		if (fchar_is_token(tr + count, str, &i) == SUCCESS)
			++count;
		else
			flongest_token(tr + count, str, &i, &count);
	}
}

static int	token_count(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (*(str + i))
	{
		while (*(str + i) == ' ')
			++i;
		if (char_is_token(*(str + i), *(str + i + 1), &i) == SUCCESS)
			++count;
		else
			longest_token(str, &i, &count);
	}
	return (count);
}

t_leaf	*lexer(t_cmd *hll)
{
	if ((*hll).str == NULL)
		return (NULL);
	(*hll).count = token_count((*hll).str) + 2;
	(*hll).tr = malloc((*hll).count * sizeof(t_leaf));
	if ((*hll).tr == NULL)
		return (NULL);
	fill_tree((*hll).str, (*hll).tr);
	fill_leaf((*hll).tr + (*hll).count - 1, -1, 0, NULL);
	fill_leaf((*hll).tr + (*hll).count - 2, NL, 0, NULL);
	return ((*hll).tr);
}
