#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct{
	pthread_mutex_t mutex;
	sem_t sem;
	int value;
	int reader_counter;
} _data;

_data* init_data(int* retval);

void write_data(_data* data_to_write, int new_value);

void* writer(void*);

void read_data (_data* data_to_read, int* ret_value);

void* reader(void*);

int main () {
	srand(time(0));
	_data* data = init_data(NULL);
	pthread_t w_id, r_id;
	pthread_create(&w_id, NULL, &writer, (void*)data);
	pthread_create(&r_id, NULL, &reader, (void*)data);
	pthread_join(w_id, NULL);
	pthread_join(r_id, NULL);

}

_data* init_data(int* retval) {
	_data* new_data = malloc(sizeof(_data));
	int return_value;
	return_value = pthread_mutex_init(&(new_data->mutex), NULL);
	if (!return_value) //se mutex inizializzato con successo
		return_value = sem_init(&(new_data->sem), 0, 1);

	if (retval != NULL)
		retval = &return_value;

	if(!return_value) //se sem inizializzato con successo
		return new_data;

	return NULL;
}

void write_data(_data* data_to_write, int new_value) {
	sem_wait(&(data_to_write->sem));
	// inizio SC
	printf("writer wrote: %d\n",new_value);
	data_to_write->value = new_value;
	// fine SC
	sem_post(&(data_to_write->sem));
}

void* writer(void* data) {
	_data* data_to_write = (_data*)data;
	while (1)
		write_data(data_to_write, random()%1000+1);
}

void read_data(_data* data_to_read, int* ret_value) {
	pthread_mutex_lock(&(data_to_read->mutex));
	data_to_read->reader_counter++;
	if (data_to_read->reader_counter == 1)
		sem_wait(&(data_to_read->sem));

	pthread_mutex_unlock(&(data_to_read->mutex));
	// inizio SC
	*ret_value = data_to_read->value;
	printf("reader has read: %d\n",*ret_value);
	// fine SC
	pthread_mutex_lock(&(data_to_read->mutex));
	if (!(data_to_read->reader_counter));
		sem_post(&(data_to_read->sem));

	pthread_mutex_unlock(&(data_to_read)->mutex);
}

void* reader(void* data) {
	_data* data_to_read = (_data*)data;
	int* readed = malloc(sizeof(int));
	while(1)
		read_data(data_to_read, readed);
}
