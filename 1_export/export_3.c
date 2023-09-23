#include	<stdio.h>
#include	"minishell.h"

void	print_va(t_lv *va)
{
	int	i;

	if (va == NULL)
		return ;
	i = -1;	
	while ((*(va + (++i))).name)
		printf("declare -x %s=\"%s\"\n", (*(va + i)).name, (*(va + i)).content);
}
