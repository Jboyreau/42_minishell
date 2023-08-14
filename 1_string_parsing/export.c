#include <stdlib.h>
#include "minishell.h"

#define SUCCESS 0
#define FAILURE 1

t_lv	*destroy_va(t_lv *va)
{
	int i;

	if (va == NULL)
		return (NULL);
	i = 0;
	while ((*(va + i)).name)
	{
		free((*(va + i)).name);	
		++i;
	}
	free(va);
	return (NULL);
}

char	allocate_var_name(char *var, char **name, char **content, int len)
{
	int		i;
	int		j;

	i = 0;
	while (*(var + i))
		++i;
	*name = malloc(i + 1);
	if (*name == NULL)
		return (FAILURE);
	i = -1;
	j = 0;
	while (*(var + (++i)) != '=' && i < len)
		*(*name + i) = *(var + i);
	*(*name + i) = 0;
	*content = *name + (++i);
	j = 0;
	while (*(var + i + j) && i +j < len)
	{
		*(*content + j) = *(var + i + j);
		++j;
	}
	*(*content + j) = 0;
	return (SUCCESS);
}


t_lv	*ft_export(t_lv *va, char **env, char *variable, int len)
{
	static char *content;
	static char *name;

	if (variable)
		if (allocate_var_name(variable, &name, &content, len) == FAILURE)
			return (NULL);
	va = export_var(va, name, content, env);
	return (va);
}
