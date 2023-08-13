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

t_cmd	*lexer(t_cmd *hll)
{
	(*hll).count = token_count((*hll).str);
	(*hll).tr = malloc((*hll).count * sizeof(t_leaf));
	if ((*hll).tr == NULL)
		return (NULL);
	fill_tree((*hll).str, (*hll).tr);
//debug
	int i = 0;
	t_leaf *tr = (*hll).tr;
	printf("token count = %d\n", (*hll).count);
	while (i < (*hll).count)
	{
		printf("\t{len = %d, type = %d --> ", (*(tr + i)).len, (*(tr + i)).type);
		for (int j = 0; j < (*(tr + i)).len; ++j){printf("%c", *((*(tr + i)).word + j));}
		printf("}\n");
		++i;
	}
	putchar('\n');
	return (hll);
}
