#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sig_handler(int sig)
{
	putchar('\n');
}

int main(int argc, char *arg, char **env)
{
	char *cmd = "./prg";
	char *tab[] = {cmd, NULL};
	int	status;
	int mask = 255;
	pid_t pid;

	signal(SIGINT, sig_handler);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, tab, env);
		printf("errno = %d\n", errno);
		exit(125 + errno);
	}
	waitpid(pid, &status, 0);
	printf("termination signal: %d\n", status & mask); //bash returns 128 + trem_sig
	printf("exit status: %d\n", status >> 8);
	return (0);
}
