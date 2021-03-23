// License: CC BY-NC-SA 4.0
/*
 * Stack.h
 *
 * Stack, based on linked list.
 *
 * Written by AlexeyFilich
 * 23 mar 2021
 */

#ifndef STACK_H
#define STACK_H

struct Stack {
    void * data;
    struct Stack * parent;
};
typedef struct Stack Stack;

void aStackInit(Stack ** stack) {
    *stack = NULL;
}

#define aStackPush(stack, data) \
    aStackPushType(stack, data, sizeof(*(data)))

void aStackPushType(Stack ** stack, void * data, size_t element_size) {
    Stack * next = (Stack *)malloc(sizeof(Stack));
    next->data = malloc(element_size);
    memcpy(next->data, data, element_size);
    next->parent = *stack;
    *stack = next;
}

void aStackPop(Stack ** stack) {
    Stack * prev = *stack;
    if (*stack == NULL) {
        printf("error: stack is empty\n");
        exit(-1);
    }
    *stack = (*stack)->parent;
    free(prev->data);
    free(prev);
}

#define aStackTopAs(stack, type) \
    *(type *)aStackTop(stack)

void * aStackTop(Stack ** stack) {
    if (*stack == NULL) {
        printf("error: stack is empty\n");
        exit(-1);
    }
    return (*stack)->data;
}

#ifdef STORAGE_SPECIAL_CASES
    void aStackPushI(Stack ** stack, int data) {
        aStackPush(stack, &data);
    }

    void aStackPushF(Stack ** stack, float data) {
        aStackPush(stack, &data);
    }

    void aStackPushC(Stack ** stack, char data) {
        aStackPush(stack, &data);
    }

    int aStackTopI(Stack ** stack) {
        return *(int *)aStackTop(stack);
    }

    float aStackTopF(Stack ** stack) {
        return *(float *)aStackTop(stack);
    }

    char aStackTopC(Stack ** stack) {
        return *(char *)aStackTop(stack);
    }
#endif

#endif
