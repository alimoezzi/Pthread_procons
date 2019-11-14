#include<pthread.h>
#include<cstdio>
#include<cstdlib>

#define BUF_SIZE 3

int buffer[BUF_SIZE]; //shared buffer
int add = 0; //index of next element
int rem = 0; //index to remove the next element
int size = 0; //buffer size

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producers(void *param);
void *consumers(void *param);

int main() {
	pthread_t tid1, tid2; //thread identifiers
	int i;
	if (pthread_create(&tid1, NULL/*behav attr*/, producers, NULL /*args*/) != 0) {
		fprintf(stderr, "Producer thread creation failed");
		exit(1);
	}
	
	if (pthread_create(&tid2, NULL, consumers, NULL) != 0) {
		fprintf(stderr, "Consumer thread creation failed");
		exit(1);
	}

	pthread_join(tid1,NULL); //producer exit
	pthread_join(tid2, NULL); //consumer exit

	puts("program ended");
	return 0;
}


void * producers(void * param) {
	for (int i = 0; i < 20; i++) {
		pthread_mutex_lock(&m);
		if (size > BUF_SIZE) exit(0); //overflow
		while (size == BUF_SIZE) { //block if buffer is full
			pthread_cond_wait(&c_prod, &m);
		}
		buffer[add] = i;
		printf("	producer inserted %d @ %d\n", i, add);
		add = (add + 1) % BUF_SIZE;
		size++;
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c_cons);
	}
	puts("producer ending\n");
	return 0;
}

void * consumers(void * param) {
	int i = 0;
	do {
		pthread_mutex_lock(&m);
		while (size == 0 and i < 19) { //block if buffer is empty
			pthread_cond_wait(&c_cons, &m);
		}
		if (i == 19) break;
		i = buffer[rem];
		printf("consume %d @ %d\n", i, rem);
		rem = (rem + 1) % BUF_SIZE;
		size--;
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c_prod);
	} while (size > -1);

	puts("consumer ending\n");
	return 0;
}

