all:
	gcc -Wall -Werror -Wextra -g3 *.c -lreadline
fclean:
	rm ./a.out
