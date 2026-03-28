#pragma once
#include "queue.h"
#include "graphh.h"

Queue_t* create_queue(Graph_t* pGraph)
{
	Queue_t* pQueue = (Queue_t*)malloc(sizeof(Queue_t));

	if (pQueue == NULL) {
		perror("Alocation for Queue Failed!!!");
		return NULL;
	}

	pQueue->start = 0;
	pQueue->end = 0;
	pQueue->capacity = pGraph->num_vertex;
	pQueue->pArr = (int *)calloc(1, sizeof(int) * pGraph->num_vertex);

	return pQueue;
}

bool enqueue(Queue_t* pQueue, int index)
{
	if (isFull(pQueue))
	{
		return false;
	}

	pQueue->pArr[pQueue->end] = index;
	pQueue->end = (pQueue->end + 1) % pQueue->capacity;

	return true;
}

int dequeue(Queue_t* pQueue)
{
	if (!isEmpty(pQueue))
	{
		int value = pQueue->pArr[pQueue->start];
		pQueue->start = (pQueue->start + 1) % pQueue->capacity;
		return value;
	}

	return -1;
}

bool isFull(Queue_t* pQueue)
{
	if (((pQueue->end + 1) % pQueue->capacity) == pQueue->start)
		return true;
	else
		return false;
}

bool isEmpty(Queue_t* pQueue)
{
	if (pQueue->end == pQueue->start)
		return true;
	else
		return false;
}