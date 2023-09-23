#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define DOUBLE_QUOTE '"'
#define SIMPLE_QUOTE '\''
#define SUCCESS 0
#define FAILURE 1

char	find_n_name(char *name, t_lv *va, int *l, int n)
{
	int	i;
	int j;

	i = -1;
	while ((*(va + (++i))).name)
	{
		j = -1;
		while (*((*(va + i)).name + (++j)) && j < n)
			if (*((*(va + i)).name + j) != *(name + j))
				break ;
		if (*((*(va + i)).name + j) == 0 && n == j)
			return (*l = i, SUCCESS);
	}
	return (FAILURE);
}

char	is_metachar(char c)
{
	return (c == '"' || c == '\'' || c == '$' || c == '&'
		|| c == '|' || c == '<' || c == '>' || c == '@'
			|| c == '=' || c == '#' || c == '.' || c == '/'
				|| c == ',' || c == '%' || c == '-' || c == '*'
					|| c == '+' || c == '!' || c == ':'
						|| c == '~' || c == '^' || c == '{'
							|| c == '}' || c == '\\' || c == '['
								|| c == ']');
}

char	string_sub2(char **str, t_lv *va)
{
	int			len;
	t_string	new;

	len = string_len2(*str, va);
	new.cursor = 0;
	new.content = malloc(len + 1);
	if (new.content == NULL)
		return (FAILURE);
	if (len == 0)
		*(new.content) = '\0';
	else
		string_cpy2(str, va, &new);
	free(*str);
	*str = new.content;
	return (SUCCESS);
}
