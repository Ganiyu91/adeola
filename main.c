#include "buffered_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct buffered_queue queue;

void *generate_message(void *ptr);
void *print_message( void *ptr );

int main() {
    pthread_t producer1, producer2, consumer1;
    int id[2];
    id[0] = 0;
    id[1] = 1;
    buffered_queue_init(&queue,5);
    pthread_create( &producer1, NULL, generate_message, &id[0]);
    pthread_create( &producer2, NULL, generate_message, &id[1]);
    pthread_create( &consumer1, NULL, print_message, NULL);

    pthread_join( producer1, NULL);
    pthread_join( producer2, NULL);
    pthread_join( consumer1, NULL);

    buffered_queue_destroy(&queue);
    return 0;
}

void *generate_message(void *ptr){
    int myid = *(int *)ptr;
    int i;
    for(int i=0; i<100; i++){
	char *msg = malloc(sizeof(char)*100);
        sprintf(msg, "msg from producer %d, value=%d", myid, i);
        buffered_queue_push(&queue, msg);
    } 
    return NULL;
}

void *print_message( void *ptr ){
    while(1){
	char * msg = (char *)buffered_queue_pop(&queue);
        printf("consumer gets %s\n", msg);
        free(msg);
    }
    return NULL;
}

