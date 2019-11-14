#include"procon.cpp"

void * producers(void * param) {
	for (int i = 0; i < 20; i++) {
		pthread_mutex_lock(&m);
		if (size > BUF_SIZE) exit(0); //overflow
		while (size == BUF_SIZE) { //block if buffer is full
			pthread_cond_wait(&c_prod, &m);
		}
		buffer[add++] = i;
		size++;
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c_cons);
		printf("producer inserted %d @ %d", i, size - 1);
	}

	puts("producer ending");
	return 0;
}