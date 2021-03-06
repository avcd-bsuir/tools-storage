// License: CC BY-NC-SA 4.0
/*
 * Queue.h
 *
 * Queue, based on linked list.
 *
 * Written by AlexeyFilich
 * 23 mar 2021
 */

#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
    void * data;
    struct Queue * next;
};
typedef struct Queue Queue;

void aQueueInit(Queue ** queue) {
    if (!queue) RETURN;
    *queue = NULL;
}

#define aQueuePush(queue, data) \
    aQueuePushType(queue, data, sizeof(*(data)))

void aQueuePushType(Queue ** queue, void * data, size_t element_size) {
    if (!queue) RETURN;
    if (*queue) {
        Queue * last = *queue;
        while (last->next)
            last = last->next;
        last->next = (Queue *)malloc(sizeof(Queue));
        if (!last->next) RETURN;
        last->next->data = malloc(element_size);
        if (!last->next->data) RETURN;
        memcpy(last->next->data, data, element_size);
        last->next->next = NULL;
    } else {
        *queue = (Queue *)malloc(sizeof(Queue));
        if (!*queue) RETURN;
        (*queue)->data = malloc(element_size);
        if (!(*queue)->data) RETURN;
        memcpy((*queue)->data, data, element_size);
        (*queue)->next = NULL;
    }
}

void aQueuePop(Queue ** queue) {
    if (!queue || !*queue) RETURN;
    Queue * prev = *queue;
    *queue = (*queue)->next;
    free(prev->data);
    free(prev);
}

#define aQueueFirstAs(queue, type) \
    *(type *)aQueueFirst(queue)

void * aQueueFirst(Queue ** queue) {
    if (!queue || !*queue) RETURN;
    return (*queue)->data;
}

#ifdef STORAGE_SPECIAL_CASES
    void aQueuePushI(Queue ** queue, int data) {
        aQueuePush(queue, &data);
    }

    void aQueuePushF(Queue ** queue, float data) {
        aQueuePush(queue, &data);
    }

    void aQueuePushC(Queue ** queue, char data) {
        aQueuePush(queue, &data);
    }

    int aQueueFirstI(Queue ** queue) {
        return *(int *)aQueueFirst(queue);
    }

    float aQueueFirstF(Queue ** queue) {
        return *(float *)aQueueFirst(queue);
    }

    char aQueueFirstC(Queue ** queue) {
        return *(char *)aQueueFirst(queue);
    }
#endif

#endif
