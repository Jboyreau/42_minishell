#include <stdio.h>
#include "minishell.h"

static char	end(char **folder, char *file_name)
{
	int 	i;
	int		j;
	char	*str;

	i = -1;
	while (*(folder + (++i)))
	{
		j = -1;
		str = *(folder + i);
		while (*(str + (++j)) && *(file_name + j))
			if (*(str + j) != *(file_name + j))
				break ;
		if (*(str + j) == *(file_name + j))
			return (0);
	}
	return (1);
}

void	inc(char *file_name, int last)
{
	while (last > 0)
	{
		if (*(file_name + last) == 'z')
		{
			if (last != 0)
				*(file_name + last) = 'a';
			++(*(file_name + last - 1));
		}
		else
			return ;
		--last;
	}
}

static char	add(char **folder, char *file_name, int len)
{
	int i;
	int	last;

	i = -1;
	last = len -1;
	while (++i < len)
		*(file_name + i) = 'a';
	*(file_name + len) = '\0';
	while (1)
	{
		if (end(folder, file_name))
			return (SUCCESS);
		if (*(file_name) == 'z')
			return (FAILURE);
		if (*(file_name + last) != 'z')
			++(*(file_name + last));
		else 
			inc(file_name, last);
	}
	return (SUCCESS);
}

void	back_tracking(char **folder, char *file_name)
{
	int len;

	len = 1;
	while (add(folder, file_name, len) == FAILURE)
		++len;
}
