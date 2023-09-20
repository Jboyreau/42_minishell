#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
Signals:
	SIGINT :	ctrl + c
*/

static void ctrlC_signal_handler(int sig)
{
	printf("signal handler : %d\n", sig);
}

int main (void)
{
	int a;

	printf("main : %d\n", SIGINT);
	signal (SIGINT, ctrlC_signal_handler);
	scanf("%d", &a);
	return (EXIT_SUCCESS);
}
