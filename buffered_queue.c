#include "buffered_queue.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

/* initiliaze all necessary variables for the queue */
void buffered_queue_init(struct buffered_queue *queue, int size){
	printf("buffered_queue_init");
	(queue->capacity) = size;
	(queue->length) = 0;
	(queue->front) = 0;
	(queue->end) = 0;
	(queue->entries) = malloc(size * sizeof(void*));
	pthread_cond_init(&(queue->cond), NULL);
	pthread_mutex_init(&(queue->mutex), NULL);
	
}

/* push an item into the tail of the queue. If the queue is full, wait until someone pops an item */
void buffered_queue_push(struct buffered_queue *queue, void *item){
	printf("push one item\n");
	pthread_mutex_lock(&(queue->mutex));
    while ((queue->length) == (queue->capacity))
    	pthread_cond_wait(&(queue->cond), &(queue->mutex));
    //ENQUEUE

    (queue->entries[(queue->end)]) = item;
    (queue->end) = ((queue->end)+1)%(queue->capacity);
    (queue->length) = (queue->length) + 1;
	pthread_cond_broadcast(&(queue->cond));
    pthread_mutex_unlock(&(queue->mutex));

}

/* pop an item from the top of the queue. If the queue is empty, wait until someone pushes an item */
void* buffered_queue_pop(struct buffered_queue *queue){
	printf("pop one item\n");
	pthread_mutex_lock(&(queue->mutex));
	while ((queue->length) == 0)
    	pthread_cond_wait(&(queue->cond), &(queue->mutex));
    void *tmp = (queue->entries[(queue->front)]);
    (queue->length) = (queue->length) - 1;
    (queue->front) = ((queue->front)+1)%(queue->capacity);
	pthread_cond_broadcast(&(queue->cond));   
    pthread_mutex_unlock(&(queue->mutex));
    
    
    return tmp;
}

/* release all resources */
void buffered_queue_destroy(struct buffered_queue *queue){
	(queue->length) = 0;
	(queue->front) = 0;
	(queue->end) = 0;
	(queue->entries) = NULL;
	pthread_cond_destroy(&(queue->cond));
	pthread_mutex_destroy(&(queue->mutex));

	
}
