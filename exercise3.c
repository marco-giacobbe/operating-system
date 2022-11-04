/*
Scrivere un programma tale per cui quando mandato in esecuzione il processo che ne deriva genera un processo figlio
Il processo padre scrive nello standard output il proprio id e il valore di ritorno della chiamata di sistema fork e aspetta la terminazione del figlio
Il processo figlio scrive nello standard output il proprio id, il valore di ritorno della chiamata di sistema fork e l’id del padre, aspetta 5 secondi e termina
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

int main() { 

        pid_t pid = fork();

        if (pid<0) {  
                printf("Error while process creations\n");
                return 1;
        }
        else if (pid == 0){
                printf("(Figlio) la fork mi ha assegnato %d\n", pid);
                printf("(Figlio) Il mio process-id è %d\n", getpid());
                printf("(Figlio) Attendo 5 secondi e poi termino\n");
		sleep(5);
        }
        else {
                printf("(Padre) la fork mi ha assegnato %d\n", pid);
                printf("(Padre) Il mio process-id è %d\n", getpid());
		printf("(Padre) Attendo l'esecuzione del figlio\n"); 
                wait(NULL);
		printf("(Padre) Il figlio ha terminato, posso terminare\n");
        } 
}
