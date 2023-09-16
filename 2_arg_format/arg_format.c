#include <stdlib.h>
#include "minishell.h"

static char	*bidon_string_sub(t_leaf *arg, t_lv *va) // Temporary
{
	char	*new;
	int		i;

	new = malloc((*arg).len + 1);
	i = -1;
	while (++i < (*arg).len)
		*(new + i) = *((*arg).word + i);
	*(new + i) = 0;
	return (new);
}

static char ft_realloc(t_leaf *cmd, int *size)
{
	char	**new_arg;
	int		i;

	(*size) <<= 1;
	new_arg = malloc((*size) * sizeof(char *));
	if (new_arg == NULL)
		return (FAILURE);
	i = -1;
	while (*((*cmd).arg + (++i)))
		*(new_arg + i) = *((*cmd).arg + i);
	free((*cmd).arg);
	(*cmd).arg = new_arg;
	return (SUCCESS);
}

static int	arglen(char **arg)
{
	int i;

	i = 0;
	while (*(arg + i))
		++i;
	return (i);
}

char	args_to_array(t_leaf *cmd, t_leaf *arg, t_lv *va)
{
	static int size = 5;
	int len;

	if ((*cmd).arg == NULL)
	{
		(*cmd).arg = malloc(size * sizeof(char *));
		if ((*cmd).arg == NULL)
			return (FAILURE);
		*((*cmd).arg) = bidon_string_sub(arg, va); //TODO : string_sub(arg, va)
		if (*((*cmd).arg) == NULL)
			return (FAILURE);
		*((*cmd).arg + 1) = NULL;
		return (SUCCESS);
	}
	len = arglen((*cmd).arg);
	if (len + 2 > size)
		if (ft_realloc(cmd, &size) == FAILURE)
			return (FAILURE);
	*((*cmd).arg + len) = bidon_string_sub(arg, va); //TODO : string_sub(arg, va)
	if (*((*cmd).arg) == NULL)
		return (FAILURE);
	*((*cmd).arg + len + 1) = NULL;
	return (SUCCESS);
}
