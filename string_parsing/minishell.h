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

enum types
{
//Indentifiers:
	ARG,			// ARGUMENTS		0
	FIL,			// FILE				1
	CMD,			// COMMANDE			2
	LIM,			// LIMITER HEREDOC	3
//Punctuations:
	CLS_PAR,		// )				4
	NL,				// \n				5
//Operators:
	OP_PAR,			// (				6
	L_QUOTE,		// <				7
	R_QUOTE,		// >				8
	DL_QUOTE,		// <<				9
	DR_QUOTE,		// >>				10
	PIPE,			// |				11
	AND,			// &&				12
	OR,				// ||				13
//Constantes:
	STR,			// STRING == ARG d'export
	ARR,			// tableau == ARG d'export
/*******************************************************************************/
//Dans les strings:	(invisible pour le shell à l'exterieur d'une string)		/
	DOLLAR,			// $														/
	EQUAL,			// =														/
	QUOTE,			// ' (inside a string)										/
	D_D_QUOTE,		// " (inside a string)										/
	STAR,			// *														/
	VAR,			// VARIABLE													/
/*******************************************************************************/
};

typedef struct s_leaf
{
	char	type;
	int		len;
	char	*word;
	struct s_tree	*dad;
	struct s_tree	*r;
	struct s_tree	*l;
} t_leaf;

typedef struct s_commands
{
	char	*str;
	t_leaf	*tr;
	int		count;
} t_cmd;

char	char_is_token(char c0, char c1, int *i);
char	fchar_is_token(t_leaf *tr, char *str, int *i);
void	longest_token(char *str, int *i, int *count);
void	flongest_token(t_leaf *tr, char *str, int *i, int *count);
void	fill_leaf(t_leaf *tr, char type, int len, char *word);
t_cmd	*lexer(t_cmd *hll);

char	parse_string(t_leaf *node);
#endif
