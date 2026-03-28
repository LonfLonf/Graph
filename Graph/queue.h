#pragma once
#include <stdbool.h>

typedef struct Graph Graph_t;

typedef struct Queue {
	int start;
	int end;
	int capacity;
	int* pArr;
} Queue_t;

Queue_t* create_queue(Graph_t* pGraph);
bool enqueue(Queue_t* pQueue, int index);
int dequeue(Queue_t* pQueue);
bool isFull(Queue_t* pQueue);
bool isEmpty(Queue_t* pQueue);