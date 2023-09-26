NAME=minishell

SRC=arg_format.c arg_variable.c builtins.c cd.c echo.c env.c\
	exec_1.c exec_2.c exec_3.c exec.c exec_sub.c\
	exec_utils.c exit.c export_1.c export_2.c export_3.c\
	export_4.c export.c ft_split.c get_next_line.c get_next_line_utils.c\
	heredoc_1.c heredoc.c heredoc_utils.c lexer_1.c lexer_2.c\
	lexer_3.c lexer_4.c lexer_5.c lexer.c linked_list.c\
	minishell.c minishell_utils_2.c minishell_utils.c parser_1.c parser_2.c\
	parser_3.c parser.c parser_destroyer.c destroyer.c parser_error.c parser_init_id.c\
	parser_reset.c parser_rules1.c parser_rules.c pwd.c signal.c string_copy2.c\
	string_copy.c string_len2.c string_len.c string_sub2.c string_sub.c\
	unset.c update_status.c wildcard.c wildcard_redirect.c redirect.c


OBJ=arg_format.o arg_variable.o builtins.o cd.o echo.o env.o\
	exec_1.o exec_2.o exec_3.o exec.o exec_sub.o\
	exec_utils.o exit.o export_1.o export_2.o export_3.o\
	export_4.o export.o ft_split.o get_next_line.o get_next_line_utils.o\
	heredoc_1.o heredoc.o heredoc_utils.o lexer_1.o lexer_2.o\
	lexer_3.o lexer_4.o lexer_5.o lexer.o linked_list.o\
	minishell.o minishell_utils_2.o minishell_utils.o parser_1.o parser_2.o\
	parser_3.o parser.o parser_destroyer.o destroyer.o parser_error.o parser_init_id.o\
	parser_reset.o parser_rules1.o parser_rules.o pwd.o signal.o string_copy2.o\
	string_copy.o string_len2.o string_len.o string_sub2.o string_sub.o\
	unset.o update_status.o wildcard.o wildcard_redirect.o redirect.o

CPPFLAGS= -g3 -Wall -Wextra -Werror

CFLAGS= -lreadline

all : $(NAME)

$(NAME) : $(OBJ) minishell.h
	cc $(OBJ) $(CFLAGS) -o minishell
	mkdir -p ./.tmp

clean:
	rm -f *.o

fclean: clean
	rm -f minishell

re : fclean all

#############
## PATERNS ##
#############
#$@: Nom de la regle
#$<: Nom de la premiere dÃ©pendance
#$^: Nom de la toute les dependances
%.o: %.c
	cc $(CPPFLAGS) -c $< -o $@

.PHONY: all clean fclean re
