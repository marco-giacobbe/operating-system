/* 
Scrivere un programma C, usando la libreria pthread, che
generi due thread che visualizzano nello standard output una
sequenza di un carattere, passando al thread come
argomento la lunghezza della sequenza e il carattere da
visualizzare, facendo in modo da evitare l'anomalia di terminazione
*/

#include <stdio.h>
#include <pthread.h>

void* print_something_n_times(void* something);

int main() {
	pthread_t thread_id;
	char character = 'X';
	int ntimes=50000;
	void* parameters[2];
	parameters[0] = (void*)(&character);
	parameters[1] = (void*)(&ntimes);
	pthread_create(&thread_id, NULL, &print_something_n_times, &parameters[0]);
	for (int i=0;i<5000;i++) {
		fputc('O', stderr);
	}
	pthread_join(thread_id, NULL);
}
void* print_something_n_times(void* something) {
	char something_to_print=*(*(char**)(something));
	int ntimes=*(*(int**)(something+8));
	for (int i=0;i<ntimes;i++) {
		fputc(something_to_print, stderr);
	}
	pthread_exit(NULL);
}
