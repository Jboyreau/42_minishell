#include <stdlib.h>
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

//TODO : Destroyer par va!!!

t_lv	*realloc_va(t_lv *va, int *size)
{
	t_lv	*new_va;
	int		i;

	*size <<= 1;
	new_va = malloc(*size * sizeof(va));
	if (new_va == NULL)
		return (free(va), NULL);
	i = 0;
	while ((*(va + i)).name)
	{
		(*(new_va + i)).name = (*(va + i)).name;
		(*(new_va + i)).content = (*(va + i)).content;
		++i;
	}
	free(va);
	(*(new_va + i)).name = NULL;
	return (new_va);
}

int	va_len(t_lv *va)
{
	int len;

	len = 0;
	while ((*(va + len)).name)
		++len;
	return (len);
}


char	env_to_va(char *var, t_lv *va)
{
	int		i;
	int		j;

	i = 0;
	while (*(var + i))
		++i;
	(*va).name = malloc(i);
	if ((*va).name == NULL)
		return (FAILURE);
	i = -1;
	j = 0;
	equal = 0;
	while (*(var + (++i)) != '=')
		*((*va).name + i) = *(var + i);
	*((*va).name + i) = 0;
	(*va).content = (*va).name + (++i);
	j = 0;
	while (*(var + i))
	{
		*((*va).content + j) = *(var + i + j);
		++j;
	}
	*((*va).content + j) = 0;
	return (SUCCESS);
}

static char	va_init(t_lv *va, char **env)
{
	len = 0;
	while (*(env + len))
		++len;
	va = malloc((len + 1) * sizeof(va));
	if (va == NULL)
		return (FAILURE);
	len = -1;
	while (*(env + (++len)))
		if (env_to_va(*(env + len), va + len) == FAILURE)
			return (free(va), NULL);
	(*(va + len)).name = NULL;
	return (SUCCESS);
}

t_lv	*export_var(t_lv *va, char *name, char *content, char **env)
{
	static int	size = 10;
	int			len;

	if (va == NULL)
		if (va_init(va, env) == FAILURE)
			return (NULL);
	len = va_len(va);
	if (len + 2 > size)
	{
		va = realloc_va(va, &size);
		if (va == NULL)
			return (NULL);
	}
	(*(va + len - 1)).name = name;
	(*(va + len - 1)).content = content;
	(*(va + len)).name = NULL;
	return (va);
}
