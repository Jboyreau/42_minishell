#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

t_lv	*realloc_va(t_lv *va, t_lv **new_va, int *size)
{
	int		i;

	*size <<= 1;
	*new_va = malloc(*size * sizeof(t_lv));
	if (*new_va == NULL)
		return (va);
	i = 0;
	while ((*(va + i)).name)
	{
		(*((*new_va) + i)).name = (*(va + i)).name;
		(*((*new_va) + i)).content = (*(va + i)).content;
		++i;
	}
	free(va);
	(*((*new_va) + i)).name = NULL;
	return (*new_va);
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
	(*va).name = malloc(i + 1);
	if ((*va).name == NULL)
		return (FAILURE);
	i = -1;
	j = 0;
	while (*(var + (++i)) != '=')
		*((*va).name + i) = *(var + i);
	*((*va).name + i) = 0;
	(*va).content = (*va).name + (++i);
	j = 0;
	while (*(var + i + j))
	{
		*((*va).content + j) = *(var + i + j);
		++j;
	}
	*((*va).content + j) = 0;
	return (SUCCESS);
}

static char	va_init(t_lv **va, char **env, int *size)
{
	int len;

	*size = 0;
	while (*(env + (*size)))
		++(*size);
	(*size) <<= 1;
	*va = malloc((*size) * sizeof(t_lv));
	if (*va == NULL)
		return (FAILURE);
	len = -1;
	while (*(env + (++len)))
		if (env_to_va(*(env + len), (*va) + len) == FAILURE)
			return (FAILURE);
	(*((*va) + len)).name = NULL;
	return (SUCCESS);
}

t_lv	*export_var(t_lv *va, char *n, char *c, char **env)
{
	static int	size;
	t_lv		*new_va;
	int			l;

	if (va == NULL)
	{
		if (va_init(&va, env, &size) == FAILURE)
			return (destroy_va(va));
		return (va);
	}
	if (find_name(n, va, &l) == SUCCESS)
	{
		free((va[l]).name);
		return ((va[l]).content = c, (va[l]).name = n, va);
	}
	l = va_len(va);
	if (l + 2 > size)
	{
		va = realloc_va(va, &new_va, &size);
		if (new_va == NULL)
			return (destroy_va(va));
	}
	return ((va[l]).name = n, (va[l]).content = c, (va[l + 1]).name = NULL, va);
}
