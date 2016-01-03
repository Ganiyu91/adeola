#ifndef _BUFFERED_QUEUE_H
#define _BUFFERED_QUEUE_H
#include <pthread.h>

/* do not use any global variables in this file */

struct buffered_queue{
	int capacity;
	int length;
	int front;
	int end;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_t **entries;
	
    /* define all necessary variables here */
};

void buffered_queue_init(struct buffered_queue *queue, int size);

void buffered_queue_push(struct buffered_queue *queue, void *item);

void* buffered_queue_pop(struct buffered_queue *queue);

void buffered_queue_destroy(struct buffered_queue *queue);

#endif
