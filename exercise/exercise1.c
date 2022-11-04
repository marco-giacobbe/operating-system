/* 
Scrivere un programma che generi un processo figlio. 
Il padre dovrà scrivere a video “output del processo padre”
Il figlio dovrà scrivere a video “output del processo figlio”

*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main() {

	pid_t pid = fork();
	if (pid<0) {
		printf("Error while process creations\n");
	}
	else if (pid == 0) {
		printf("output del processo figlio\n");
	}
	else {
		printf("output del processo padre\n");
		wait(NULL);
	}
}
