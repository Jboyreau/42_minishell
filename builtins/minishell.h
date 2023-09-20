#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_leaf
{
	char	f_type;
	char	type;
	int		len;
	char	*word;
	char	**arg;
	struct s_leaf	*dad;
	struct s_leaf	*right;
	struct s_leaf	*left;
	struct s_leaf	*next;
} t_leaf;