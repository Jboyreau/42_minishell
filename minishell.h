#ifndef MINISHELL_H
# define MINISHELL_H

extern int subindex; //A ENLEVER ------------------------

#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

extern short int	g_signal;

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

typedef unsigned long long int	t_rule_elem;

typedef t_rule_elem	t_r;

typedef struct	s_local_var
{
	char	*name;
	char	*content;
} t_lv;

typedef struct s_leaf
{
	char	f_type;
	char	type;
	int		fdl;	//limiter file descriptor
	int		len;
	char	*word;
	char	**arg;
} t_leaf;

typedef struct	s_commands
{
	char	*str;
	t_leaf	*tr;
	t_lv	*va;
	t_r		*start;
	char	*str1;
	char	*str2;
	char	ret;
	int		count;
	int		len;
	int		len1;
	struct sigaction new_action;
} t_cmd;

typedef struct	s_location
{
	t_rule_elem	*prev;
	int			index;
} t_loc;

typedef struct	s_rule_state
{
	int			size;
	int			lstate;
	int			id;
} t_rs;

typedef struct s_exec
{
	char	cmd_pos;
	int		nb_of_cmd;
	pid_t	last_pid;
	int		save_first;
	int		sub_end;
	char	**env;
	int 	status;
	t_cmd	*cmd_ptr;
}				t_exec;

typedef struct s_string
{
	char	*content;
	int		cursor;
}				t_string;

typedef struct s_list
{
	char	*content;
	struct	s_list *next;
}				t_list;

typedef struct s_str_array
{
	char	**ptr;
	int		size;
}				t_str_array;

//Lexer:
char		only_space(char *str);
char		char_is_token(char c0, char c1, int *i);
char		fchar_is_token(t_leaf *tr, char *str, int *i);
void		longest_token(char *str, int *i, int *count);
void		flongest_token(t_leaf *tr, char *str, int *i, int *count);
void		fill_leaf(t_leaf *tr, char type, int len, char *word);
t_leaf		*lexer(t_cmd *hll);
char        rev_char_is_token(char c0, char c1, int *j);
char		is_space(int i_space, char *str);
char		is_token(int i_op, int *i, char *str);
char		fis_token(t_leaf *tr, char *str, int *i, int i_op);
char		ris_token(int i_op, int *j, char *str);

//String_parsing:
char        builtin_export(t_lv **va, char **env, t_leaf *cmd);
char        ft_export(t_lv **va, char **env, char *variable, int len);
t_lv		*export_var(t_lv *va, char *name, char *content, char **env);
t_lv		*destroy_va(t_lv *va);
char		find_name(char *name, t_lv *va, int *l);
void		print_va(t_lv *va);
//Arg_format:
char		args_to_array(t_leaf *cmd, t_leaf *arg, t_lv *va);
char		args_to_array_wildcard(t_leaf *cmd, char *filename);
//Syntaxe analysis:
t_rule_elem	*init_rules();
t_rule_elem	*init1(t_r *red, t_r *tst, t_r *suf);
t_rule_elem	*init_id(t_rule_elem *prompt);
char		parser(t_leaf *tr, t_rule_elem *rule);
char		print_error(int type, char *word, int len);
void		parser_destroyer(t_rule_elem *prompt);
char		firstof_all(t_r **rule, char typ, char *f_typ);
char		firstof_one(t_r **rule, char type, char *f_type, int i);
char		dive(int i, t_r **rule);
char		stay(t_r **rule, char type, char *f_type, int i);
char		ascend(t_r **rule);
void		reset_state(t_rule_elem *pt);
char		ft_alloc_loc(t_rs *state, t_r *loc);
char		c(t_leaf *tr);
char		d(t_leaf *tr);
char        e(t_leaf *tr);

//String sub

char		*string_sub(t_leaf *tok, t_lv *va);
int			ft_strlen(const char *s);
char		is_metachar(char c);
char		find_n_name(char *name, t_lv *va, int *l, int n);
char		string_cpy(t_leaf *tok, t_lv *va, t_string *str);
uint		string_len(t_leaf *tok, t_lv *va);
void		ft_putnbr_q(int n, t_string *str);
int			sig_len(void);

//Execute
void	execute_tree(t_leaf *tree, t_lv *va);
void	open_pipe(int *pipefd, char cmd_pos, t_cmd *hll);
void	execute(t_cmd *hll, t_leaf *token, char **env);
pid_t	exec_pipeline(t_leaf *cmd, t_exec *ex, int i, int *pipefd);
void	redirect_pipe(int *pipefd, char cmd_pos);
pid_t	pipe_subshell(t_leaf *cmd, t_exec *ex, int *pipefd);
void	clean_prompt(t_leaf **token);
int		execute_sub(t_cmd *hll, t_leaf *token, int i, char **env);
int		pre_redir(t_leaf *token, int i, t_exec *ex);
int		suf_redir(t_leaf *token, t_exec *ex);
bool	ft_split(t_str_array *array, char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	exec_cmd(t_leaf	*cmd, int i, t_exec *ex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	last_par(t_leaf *token, int *i);
char	check_sub_pos(t_leaf *token, int fpar, int lpar);
char	check_cmd_pos(t_leaf *token, int i);
int		wait_cmd(int nb_of_cmd, pid_t last_pid);
int		wait_cmd_sub(int nb_of_cmd, pid_t last_pid);
void	handle_sub_command(t_exec *ex, t_leaf *tok, int i, int *pipefd);
void	handle_subshell(t_leaf *token, int *i, int *pipefd, t_exec *ex);
int		update_exit_stat(t_lv *va, int code);

//Heredoc
char		heredoc(t_leaf *tr);
void		back_tracking(char **folder, char *file_name);
//Utils
void		d_folder(void *folder);
char		cmp_lim_str(char *str, char *word, int len, int i);
char		*ft_strdup(const char *s);
int			ft_strlen1(char	*str);
int			ft_readline1(char **line, const char *prompt);
//Heredoc sub
char			string_sub2(char **str, t_lv *va);
unsigned int	string_len2(char *str, t_lv *va);
char			string_cpy2(char **str, t_lv *va, t_string *new);

//Destroyer
void	destroy_arg(t_leaf *tr);

//Linked list
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst);

//signal
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

//Builtins
void	builtins_check(t_leaf *cmd, t_exec *ex);
int		ft_echo(t_leaf *cmd);
int		ft_pwd(void);
int		ft_cd(t_leaf *cmd);
int		ft_exit(t_leaf *cmd, t_exec *ex);
char	is_nofork_builtin(t_leaf *cmd);
int		nofork_builtins_exec(t_leaf *cmd, int i, t_exec *ex);
int 	unset(t_lv *va, char** arg);
int		env(t_lv *va);

//Destroyer
void	dall(t_lv *va, t_r *start);
void	dll(char **str, t_leaf **tr);
void	ft_str_array_free(t_str_array *array);
void	exit_failure(t_cmd *hll);
void	destroy_arg_child(t_leaf *tr);
void	dll_child(char **str, t_leaf **tr);

//Wildcard
int		wildcard(t_leaf *cmd, t_leaf *arg);
int		wildcard_redirect(char *file);

#endif

