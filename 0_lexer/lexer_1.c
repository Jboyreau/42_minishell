#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

char	char_is_token(char c0, char c1, int *i)
{
	char *t;

	t = ")\n(<>|";

	if ((c0 == '<' || c0 == '>' || c0 == '|' || c0 == '&') && (c0 == c1))
			return ((*i) += 2, SUCCESS);
	while (*t)
	{
		if (c0 == *t)
			return (++(*i), SUCCESS);
		++t;
	}
	return (FAILURE);
}

static void	normal_string(char *str, int *i, int *count)
{
	while (*(str + (*i)))
	{
		if (*(str + (*i)) == ' ')
			return (++(*count), (void)0);
		if (char_is_token(*(str + (*i)), *(str + (*i) + 1), i) == SUCCESS)
			return (*count += 2, (void)0);
		++(*i);
	}
	return (++(*count), (void)0);
}

static void	dq_sequence(char *str, int *i, int *count)
{
	int			j;
	int			quote;
	static int	bidon;

	j = *i + 1;
	quote = 0;
	while (*(str + j))
	{
		if (*(str + j) == '\"')
			quote = 1;
		if (quote && char_is_token(*(str + j), *(str + j + 1), &bidon) == SUCCESS)
			break ;
		++j;
	}
	while (*(str + j) != '\"')
		--j;
	if (*i == j)
		return (normal_string(str, i, count));
	return (*i = j + 1, ++(*count), (void)0);
}

static void	q_sequence(char *str, int *i, int *count)
{
	int			j;
	int			quote;
	static int	bidon;

	j = *i + 1;
	quote = 0;
	while (*(str + j))
	{
		if (*(str + j) == '\'')
			quote = 1;
		if (quote && char_is_token(*(str + j), *(str + j + 1), &bidon) == SUCCESS)
			break ;
		++j;
	}
	while (*(str + j) != '\'')
		--j;
	if (*i == j)
		return (normal_string(str, i, count));
	return (*i = j + 1, ++(*count), (void)0);
}

void	longest_token(char *str, int *i, int *count)
{
	if (*(str + (*i)) == '\'')
		return (q_sequence(str, i, count));
	if (*(str + (*i)) == '\"')
		return (dq_sequence(str, i, count));
	return (normal_string(str, i, count));
}
