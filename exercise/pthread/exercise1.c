/*
Scrivere un programma C, usando la libreria pthread, che
generi due thread che visualizzano nello standard output una
sequenza infinita rispettivamente del carattere ‘x’ e ‘o’
*/

#include <stdio.h>
#include <pthread.h>

void* print_x(void* something);

int main() {
	pthread_t print_x_id;
	pthread_create(&print_x_id, NULL, &print_x, NULL);
	while (1) {
		printf("O");
	}
}

void* print_x(void* something) {
	while(1) {
		printf("X");
	}
}
