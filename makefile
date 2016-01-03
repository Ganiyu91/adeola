all: main.c buffered_queue.c
	gcc -std=c99 -o main -lpthread main.c buffered_queue.c -I.
