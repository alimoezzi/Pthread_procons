#pragma once
#ifndef PROCON_H
#define PROCON_H

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

#endif // !PROCON_H
