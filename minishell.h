#ifndef MINISHELL_H
# define MINISHELL_H
/*	Token types:
	{
		Indentifiers	:
			files
			variables
			commandes arg0 arg1 arg2 ... arg n

		Punctuations	:
			\n
			)

		Keywords		:
			'		(dans une séquence entre guillemets)
			"		(dans une séquence entre guillemets, ne marche pas pour $)

		Operators		:
			(	unary
					string)
			<	binary/unary	(input redirection)
					commande < file
					< file (sans commande spécifié, lit stdin à partir de file sans rien faire d'autre)
			>	binary			(output redirection)
					commande > file
			>>  binary			(output redirection append)
					commande >> file
			<<	binary/unary	(input redirection and heredoc)
					commande << LIMITER
					<< LIMITER (sans commande spécifié, lit stdin à partir d'stdin sans rine faire d'autre)
			|	binary
					cmd | cmd
			&&	binary		(go yt)
					cmd && cmd
			||	binary		(go yt)
					cmd || cmd

		Constantes(export param) :
			string	"Alice" ou Alice
			tableau	("rouge" "vert" "bleu")
			=	binary			(affecte une valeur à une variable)
					variable = value

		Dans les strings:
			*	binary/unary	(se substitue par tous les noms de fichiers du dossier courant, la commande est dupliquée autant de fois qu'il y a une correspondance entre les fichiers du dossier et l'operand)
					commande *string
					commande ...*...
					*string
					...*...
			$	unary			(substite l'operand et l'operateur par une valeur)
					string
					?		(fait référence à une variable contenant le statut de sortie de la derniere commande)
	}
*/

enum ret
{
	SUCCESS,
	FAILURE,
	MEM_FAIL,
};

enum types
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

enum file_type
{
	CMD,	//commande	0
	ARG,	//argument	1
	LIM,	//limiter	2
	FIL,	//file		3
};

enum rule_id
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

enum production_result
{
	DIVE,
	STAY,
	ASCEND,
	QUIT,
};

typedef unsigned long long int rule_elem;

typedef	rule_elem r;

typedef struct	s_local_var
{
	char	*name;
	char	*content;
} t_lv;

typedef struct s_leaf
{
	char	f_type;
	char	type;
	int		len;
	char	*word;
	char	**arg;
	struct s_tree	*dad;
	struct s_tree	*r;
	struct s_tree	*l;
} t_leaf;

typedef struct	s_commands
{
	char	*str;
	t_leaf	*tr;
	t_lv	*va;
	r		*start;
	char	*str1;
	char	*str2;
	char	ret;
	int		count;
	int		len;
	int		len1;
} t_cmd;

typedef struct	s_location
{
	rule_elem	*prev;
	int			index;
} t_loc;

typedef struct	s_rule_state
{
	int			size;
	int			lstate;
	int			id;
} t_rs;

//Lexer:
char		char_is_token(char c0, char c1, int *i);
char		fchar_is_token(t_leaf *tr, char *str, int *i);
void		longest_token(char *str, int *i, int *count);
void		flongest_token(t_leaf *tr, char *str, int *i, int *count);
void		fill_leaf(t_leaf *tr, char type, int len, char *word);
t_leaf		*lexer(t_cmd *hll);
//String_parsing:
t_lv		*ft_export(t_lv *va, char **env, char *variable, int len);
t_lv		*export_var(t_lv *va, char *name, char *content, char **env);
t_lv		*destroy_va(t_lv *va);
char		find_name(char *name, t_lv *va, int *l);
void		print_va(t_lv *va);
//Arg_format:
char		args_to_array(t_leaf *cmd, t_leaf *arg);
//Syntaxe analysis:
rule_elem	*init_rules();
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
//Execute
void execute_tree(t_leaf *tree, t_lv *va);
#endif
