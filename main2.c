#include "buffered_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct buffered_queue queue;

void *generate_message(void* ptr);
void *print_message(void* ptr);

void *sleepthread(void* ptr){
    sleep(5);
    printf("stop sleep, exit.\n");
    buffered_queue_destroy(&queue);
    exit(1);
};

int main() {
    pthread_t producer1, producer2, consumer1, consumer2;
    pthread_t sleeper;
    int id[2] ={1,2};
    buffered_queue_init(&queue,5);
    pthread_create( &producer1, NULL, generate_message, &id[0]);
    //pthread_create( &producer2, NULL, generate_message, &id[1]);
    pthread_create( &consumer1, NULL, print_message, NULL);
    pthread_create( &consumer2, NULL, print_message, NULL);
    pthread_create(&sleeper, NULL, sleepthread,NULL);
    
    //pthread_join( producer1, NULL);
    //pthread_join( comsumer2, NULL);
    pthread_join( consumer1, NULL);
    pthread_join( consumer2,NULL);
    buffered_queue_destroy(&queue);
    return 0;
}

void *generate_message(void *ptr){
    int myid = *(int *)ptr;
    int i;
    for(i=0; i<5; i++){
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
