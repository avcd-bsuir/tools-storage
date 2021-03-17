// License: CC BY-NC-SA 4.0
/*
 * Stack.h
 *
 * Stack, based on linked list.
 *
 * Written by AlexeyFilich
 * 17 mar 2021
 */

#ifndef STACK_H
#define STACK_H

#define STORAGE_SPECIAL_CASES

struct Stack {
    void * data;
    struct Stack *parent;
};
typedef struct Stack Stack;

void aStackInit(Stack **stack) {
    *stack = NULL;
}

void aStackPush(Stack **stack, void * data) {
    Stack *next = (Stack *)malloc(sizeof(Stack));
    next->data = data;
    next->parent = *stack;
    *stack = next;
}

void * aStackPop(Stack **stack) {
    Stack *prev = *stack;
    void * data = (*stack)->data;
    if (*stack == NULL) {
        printf("error: stack is empty\n");
        exit(-1);
    }
    *stack = (*stack)->parent;
    free(prev);
    prev = NULL;
    return data;
}

#define aStackPopAs(stack, type) \
    *(type *)aStackPop(stack)

void * aStackTop(Stack **stack) {
    if (*stack == NULL) {
        printf("error: stack is empty\n");
        exit(-1);
    }
    return (*stack)->data;
}

#define aStackTopAs(stack, type) \
    *(type *)aStackTop(stack)

#ifdef STORAGE_ARRAY_SPECIAL_CASES
    void aStackPushI(Stack **stack, int data) {
        aStackPush(stack, &data);
    }

    void aStackPushF(Stack **stack, float data) {
        aStackPush(stack, &data);
    }

    void aStackPushC(Stack **stack, char data) {
        aStackPush(stack, &data);
    }

    int aStackPopI(Stack **stack) {
        aStackPop(stack);
    }

    float aStackPopF(Stack **stack) {
        aStackPop(stack);
    }

    char aStackPopC(Stack **stack) {
        aStackPop(stack);
    }

    int aStackTopI(Stack **stack) {
        aStackTop(stack);
    }

    float aStackTopF(Stack **stack) {
        aStackTop(stack);
    }

    char aStackTopC(Stack **stack) {
        aStackTop(stack);
    }
#endif

#endif
