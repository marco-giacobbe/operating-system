#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

int main() {
        pid_t pid = fork();
        if (pid<0) {
                printf("Error while process creations\n");
                return 1;
        }
        else if (pid == 0) {
		exit(0);
        }
        else {
                while(1) {
			//infinite loop
		}
        }
}
