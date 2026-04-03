#pragma once

#include "stack.h"

Stack_t* create_stack(int capacity) {
    Stack_t* pStack = (Stack_t*)malloc(sizeof(Stack_t));
    if (pStack == NULL) {
        perror("Allocation for Stack Failed!!!");
        return NULL;
    }

    pStack->pArr = (int*)malloc(capacity * sizeof(int));
    if (pStack->pArr == NULL) {
        free(pStack);
        perror("Allocation for Stack Array Failed!!!");
        return NULL;
    }

    pStack->top = -1; 
    pStack->capacity = capacity;

    return pStack;
}

bool push(Stack_t* pStack, int index) {
    if (isStackFull(pStack)) {
        int new_capacity = pStack->capacity * 2;
        int* temp = (int*)realloc(pStack->pArr, new_capacity * sizeof(int));

        if (temp == NULL) {
            perror("Stack Realloc FAILED!!!");
            return false;
        }

        pStack->pArr = temp;
        pStack->capacity = new_capacity;
    }

    pStack->pArr[++(pStack->top)] = index;
    return true;
}

int pop(Stack_t* pStack) {
    if (isStackEmpty(pStack)) return -1;

    return pStack->pArr[(pStack->top)--];
}

bool isStackEmpty(Stack_t* pStack) {
    return pStack->top == -1;
}

bool isStackFull(Stack_t* pStack) {
    return pStack->top == pStack->capacity - 1;
}

void destroy_stack(Stack_t* pStack) {
    if (pStack != NULL) {
        free(pStack->pArr);
        free(pStack);
    }
}