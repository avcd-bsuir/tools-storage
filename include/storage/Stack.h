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
    if (!stack) RETURN;
    Stack * next = (Stack *)malloc(sizeof(Stack));
    if (!next) RETURN;
    next->data = malloc(element_size);
    if (!next->data) RETURN;
    memcpy(next->data, data, element_size);
    next->parent = *stack;
    *stack = next;
}

void aStackPop(Stack ** stack) {
    if (!stack || !*stack) RETURN;
    Stack * prev = *stack;
    *stack = (*stack)->parent;
    free(prev->data);
    free(prev);
}

#define aStackTopAs(stack, type) \
    *(type *)aStackTop(stack)

void * aStackTop(Stack ** stack) {
    if (!stack || !*stack) RETURN;
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
