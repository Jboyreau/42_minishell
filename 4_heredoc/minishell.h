#ifndef MINISHELL_H
# define MINISHELL_H

enum e_ret
{
	SUCCESS,
	FAILURE,
	MEM_FAIL,
};

enum e_types
{
//Indentifiers:
	W,				//					0
//Punctuations:
	CLS_PAR,		// )				1
	NL,				// \n				2
//Operators:
	L,				// <				3
	R,				// >				4
	DL,				// <<				5
	DR,				// >>				6
	OP_PAR,			// (				7
	PIPE,			// |				8
	AND,			// &&				9
	OR,				// ||				10
	Z,				// ZERO_LINK		11
};

enum e_file_type
{
	CMD,	//commande	0
	ARG,	//argument	1
	LIM,	//limiter	2
	FIL,	//file		3
};

enum e_rule_id
{
	PT_,	//0
	TST_,	//1
	TST1_,	//2
	TST2_,	//3
	P_,		//4
	P1_,	//5
	NL_,	//6
	CMD_,	//7
	CMD1_,	//8
	CMD2_,	//9
	PAR_,	//10
	PRE_,	//11
	PRE1_,	//12
	SUF_,	//13
	SUF1_,	//14
	SUF2_,	//15
	RED_,	//16
};

enum e_production_result
{
	DIVE,
	STAY,
	ASCEND,
	QUIT,
};

typedef unsigned long long int	rule_elem;
typedef unsigned long long int	r;

typedef struct s_local_var
{
	char	*name;
	char	*content;
}	t_lv;

typedef struct s_leaf
{
	char	f_type;
	char	type;
	int		fdl;	//limiter file descriptor
	int		len;
	char	*word;
	char	**arg;
}	t_leaf;

typedef struct s_commands
{
	char	*str = NULL;
	t_leaf	*tr;
	t_lv	*va;
	r		*start;
	char	*str1;
	char	*str2;
	char	ret;
	int		count;
	int		len;
	int		len1;
}	t_cmd;

typedef struct s_location
{
	rule_elem	*prev;
	int			index;
}	t_loc;

typedef struct s_rule_state
{
	int			size;
	int			lstate;
	int			id;
}	t_rs;

//Lexer:
char		char_is_token(char c0, char c1, int *i);
char		rev_char_is_token(char c0, char c1, int *j);
char		fchar_is_token(t_leaf *tr, char *str, int *i);
void		longest_token(char *str, int *i, int *count);
void		flongest_token(t_leaf *tr, char *str, int *i, int *count);
void		fill_leaf(t_leaf *tr, char type, int len, char *word);
t_leaf		*lexer(t_cmd *hll);
char		rev_char_is_token(char c0, char c1, int *j);
//String_parsing:
t_lv		*ft_export(t_lv *va, char **env, char *variable, int len);
t_lv		*export_var(t_lv *va, char *name, char *content, char **env);
t_lv		*destroy_va(t_lv *va);
char		find_name(char *name, t_lv *va, int *l);
void		print_va(t_lv *va);
//Arg_format:
char		args_to_array(t_leaf *cmd, t_leaf *arg);
//Syntaxe analysis:
rule_elem	*init_rules(void);
rule_elem	*init1(r *red, r *tst, r *suf);
rule_elem	*init_id(rule_elem *prompt);
char		parser(t_leaf *tr, rule_elem *rule);
char		print_error(int type, char *word, int len);
void		parser_destroyer(rule_elem *prompt);
char		firstof_all(r **rule, char type, char *f_type);
char		firstof_one(r **rule, char type, char *f_type, int i);
char		dive(int i, r **rule);
char		stay(r **rule, char type, char *f_type, int i);
char		ascend(r **rule);
void		reset_state(rule_elem *pt);
char		ft_alloc_loc(t_rs *state, r *loc);
char		c(t_leaf *tr);
char		d(t_leaf *tr);
char		e(t_leaf *tr);
//Execute
void		execute_tree(t_leaf *tree, t_lv *va);
//Heredoc
char		heredoc(t_leaf *tr);
void		back_tracking(char **folder, char *file_name);
//Utils
char		*ft_strdup(const char *s);
int			ft_strlen(char	*str);
#endif
