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
	if (pthread_create(&tid1,NULL,producers,NULL) != 0) {
		fprintf(stderr, "Producer thread creation failed");
		exit(1);
	}
	
	if (pthread_create(&tid2,NULL,consumers,NULL) != 0) {
		fprintf(stderr, "Consumer thread creation failed");
		exit(1);
	}

	pthread_join(tid1,NULL); //producer exit
	pthread_join(tid2, NULL); //consumer exit

	puts("program ended");
}