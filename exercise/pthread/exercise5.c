/*
Scrivere un programma multithreading costituito da
un main che svolge le seguenti funzioni:
(1) aspetta in input da stdin il nome di un file
(2) quando riceve un input genera un thread che
conta i caratteri contenuti nel file e scrive il
risultato in un altro file chiamato come il file
originale e con estensione numc
(3) torna al punto (1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* count_char_from_file(void* _filename);

int main() {
	while(1) {
		char* filename = malloc(20*sizeof(char));
		printf("Inserisci il nome del file: ");
		scanf("%s", filename);
		pthread_t* thread_id = malloc(sizeof(pthread_t));
		pthread_create(thread_id, NULL, &count_char_from_file, (void*)filename);
	}
}

void* count_char_from_file(void* _filename) {
	char* filename = (char*)_filename;
	FILE* f_open = fopen(filename, "r");
	if (f_open == NULL) {
		free(filename);
		fclose(f_open);;
		pthread_exit(NULL);
	}
	char character;
	unsigned long int counter = 0;
	do {
		character = fgetc(f_open);
		counter++;
	} while (character!=EOF);
	fclose(f_open);
	char* numc_filename = malloc((strlen(filename)+5)*sizeof(char));
	strcpy(numc_filename, filename);
	strcpy(&numc_filename[strlen(filename)], ".numc");
	FILE* numc_f_open = fopen(numc_filename, "w");
	fprintf(numc_f_open, "%ld", counter);
	fclose(numc_f_open);
	free(filename);
}
