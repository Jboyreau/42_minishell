#include <unistd.h>
#include "minishell.h"

char	print_error1(int type)
{
	if (type == DL)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, "<<", 2);
		return (write(2, "'\n", 2), FAILURE);
	}
	if (type == DR)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, ">>", 2);
		return (write(2, "'\n", 2), FAILURE);
	}
	if (type == AND)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, "&&", 2);
		return (write(2, "'\n", 2), FAILURE);
	}
	if (type == OR)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, "||", 2);
		return (write(2, "'\n", 2), FAILURE);
	}
	return (FAILURE);
}

char	print_error(int type)
{
	static char	tokens[] = "0)0<>00(|000";

	if (*(tab + type) != '0')
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, tab + type, 1);
		return (write(2, "'\n", 2), FAILURE);
	}
	if (type == NL)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, "newline", 7);
		return (write(2, "'\n", 2), FAILURE);
	}
	return (print_error1(type));
}
