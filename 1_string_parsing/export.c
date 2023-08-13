#include <stdio.h>

t_lv	*realloc_va(t_lv *va, int *size)
{
	t_lv	*new_va;
	int		i;

	*size <<= 1;
	new_va = malloc(size * sizeof(va));
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

t_lv	*export_var(t_lv *va, char *name, char *content)
{
	static int	size = 10;
	int			len;

	if (va == NULL)
	{
		va = malloc(size * sizeof(va));
		if (va == NULL)
			return (NULL);
		(*va).name = name;
		(*va).content = content;
		(*(va + 1)).name = NULL;
		return (va);
	}
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
