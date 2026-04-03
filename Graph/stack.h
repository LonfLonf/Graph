#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Graph Graph_t;

typedef struct Stack {
    int top;         
    int capacity;    
    int* pArr;       
} Stack_t;

Stack_t* create_stack(int capacity);
bool push(Stack_t* pStack, int index);
int pop(Stack_t* pStack);
bool isStackEmpty(Stack_t* pStack);
bool isStackFull(Stack_t* pStack);
void destroy_stack(Stack_t* pStack);