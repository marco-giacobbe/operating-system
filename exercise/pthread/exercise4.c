/*
Scrivere un programma che crei due threads i
quali devono stampare a video:
– il primo un simbolo dato a runtime un numero
di volte fornito dall’utente in input
- il secondo un simbolo dato a runtime un numero
di volte fornito dall’utente in input 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 2

void* print_something_n_times(void* par);

void get_parameters(void** par);

int main() {
	char characters[N_THREADS];
	int ntimes[N_THREADS];
	pthread_t t_id[N_THREADS];
	void* par[2*N_THREADS];
	for (int i=0; i<N_THREADS; i++) {
	        printf("symbol: ");
		characters[i] = getchar();
		printf("printed for: ");
		scanf("%d", &ntimes[i]);
		getchar(); //flush buffer
		par[(i*2)] = (void*)(&characters[i]);
		par[(i*2)+1] = (void*)(&ntimes[i]);
	}
	for (int i=0;i<N_THREADS;i++) {
		pthread_create(&t_id[i], NULL, &print_something_n_times, &par[i*2]);
	}
	for (int i=0;i<N_THREADS;i++) {
		pthread_join(t_id[i], NULL);
	}
}

void* print_something_n_times(void* par) {
	char something = *(*(char**)(par));
	int ntimes = *(*(int**)(par+8));
	for (int i=0;i<ntimes;i++) {
		fputc(something, stderr);
	}
	pthread_exit(NULL);
}

