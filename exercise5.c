/*
Scrivere un programma che crei un processo zombie
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main() {
	pid_t pid = fork();
	if (pid < 0) {
                printf("Error while process creations\n");
                return 1;
	}
        else if (pid == 0) {
		//sleep(1);
                printf("Sono stato affidato al processo %d\n", getppid());
        }
        else {
                exit(1);
        }
}
