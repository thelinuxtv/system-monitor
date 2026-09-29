#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../include/monitor.h"

#define TRUE 1

int main(void) {
	pid_t pid = fork();
	if (pid == 0) {
		char *arg[] = {"figlet", "system-monitor started", NULL};
		int exe = execve("/usr/bin/figlet", arg, NULL);
		if (exe == -1) {
			perror("execve");
			return -1;
		}
	}

	wait(NULL);
	
	while (TRUE) {
		printf("\n\n*****************************************************\n\n");
		print_uptime();
		print_memory();
		print_load();
		printf("\n*******************************************************\n\n");	
		fflush(stdout);

		sleep(5);
	}	

	return 0;
}
