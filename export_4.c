#include <stdlib.h>
#include "minishell.h"

char	builtin_export(t_lv **va, char **env, t_leaf *cmd)
{
	int	i;
	t_lv **zero;

	i = 0;
	while (*((*cmd).arg + (++i)))
		if (ft_export(va, env, *((*cmd).arg + i), ft_strlen(*((*cmd).arg + i))) == FAILURE)
			return (FAILURE);
	zero = NULL;
	return (ft_export(zero, env, NULL, 0));
}
