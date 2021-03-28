// License: CC BY-NC-SA 4.0
/*
 * List.h
 *
 * List, based on linked list.
 *
 * Written by AlexeyFilich
 * 27 mar 2021
 */

#ifndef LIST_H
#define LIST_H

struct List {
    void * data;
    struct List * next;
    struct List * prev;
};
typedef struct List List;

void aListInit(List ** list) {
    *list = NULL;
}

void aListFirstNodeType(List ** list, void * data, size_t element_size) {
    if (!list) RETURN;
    List * next = (List *)malloc(sizeof(List));
    if (!next) RETURN;
    next->data = malloc(element_size);
    if (!next->data) RETURN;
    memcpy(next->data, data, element_size);
    next->next = NULL;
    next->prev = NULL;
    *list = next;
}

#define aListAddEnd(list, data) \
    aListAddEndType(list, data, sizeof(*(data)))

void aListAddEndType(List ** list, void * data, size_t element_size) {
    if (!list) RETURN;
    if (!*list) {
        aListFirstNodeType(list, data, element_size);
        return;
    }
    List * last = *list;
    while (last->next)
        last = last->next;
    last->next = (List *)malloc(sizeof(List));
    if (!last->next) RETURN;
    last->next->data = malloc(element_size);
    if (!last->next->data) RETURN;
    memcpy(last->next->data, data, element_size);
    last->next->next = NULL;
    last->next->prev = last;
}

#define aListAddFront(list, data) \
    aListAddFrontType(list, data, sizeof(*(data)))

void aListAddFrontType(List ** list, void * data, size_t element_size) {
    if (!list) RETURN;
    if (!*list) {
        aListFirstNodeType(list, data, element_size);
        return;
    }
    List * first = *list;
    while (first->prev)
        first = first->prev;
    first->prev = (List *)malloc(sizeof(List));
    if (!first->prev) RETURN;
    first->prev->data = malloc(element_size);
    if (!first->prev->data) RETURN;
    memcpy(first->prev->data, data, element_size);
    first->prev->next = first;
    first->prev->prev = NULL;
}

#define aListAddAfter(list, data) \
    aListAddAfterType(list, data, sizeof(*(data)))

void aListAddAfterType(List ** list, void * data, size_t element_size) {
    if (!list) RETURN;
    if (!*list) {
        aListFirstNodeType(list, data, element_size);
        return;
    }
    List * next = (List *)malloc(sizeof(List));
    if (!next) RETURN;
    next->data = malloc(element_size);
    if (!next->data) RETURN;
    memcpy(next->data, data, element_size);
    next->next = (*list)->next;
    next->prev = (*list);
    (*list)->next = next;
    if (next->next)
        next->next->prev = next;
}

#define aListAddBefore(list, data) \
    aListAddBeforeType(list, data, sizeof(*(data)))

void aListAddBeforeType(List ** list, void * data, size_t element_size) {
    if (!list) RETURN;
    if (!*list) {
        aListFirstNodeType(list, data, element_size);
        return;
    }
    List * prev = (List *)malloc(sizeof(List));
    if (!prev) RETURN;
    prev->data = malloc(element_size);
    if (!prev->data) RETURN;
    memcpy(prev->data, data, element_size);
    prev->next = (*list);
    prev->prev = (*list)->prev;
    (*list)->prev = prev;
    if (prev->prev)
        prev->prev->next = prev;
}

void aListNext(List ** list) {
    if (!list || !*list) RETURN;
    *list = (*list)->next;
}

void aListPrev(List ** list) {
    if (!list || !*list) RETURN;
    *list = (*list)->prev;
}

void aListDelete(List ** list) {
    if (!list || !*list) RETURN;
    List * next;
    if ((*list)->prev) {
        next = (*list)->prev;
        next->next = (*list)->next;
    } else {
        next = (*list)->next;
        next->prev = (*list)->prev;
    }
    free((*list)->data);
    free(*list);
    *list = next;
}

#define aListDataAs(queue, type) \
    *(type *)aListData(queue)

void * aListData(List ** list) {
    if (!list || !*list) RETURN;
    return (*list)->data;
}

#ifdef STORAGE_SPECIAL_CASES
    void aListAddEndI(List ** list, int data) {
        aListAddEnd(list, &data);
    }

    void aListAddEndF(List ** list, float data) {
        aListAddEnd(list, &data);
    }

    void aListAddEndC(List ** list, char data) {
        aListAddEnd(list, &data);
    }

    void aListAddFrontI(List ** list, int data) {
        aListAddFront(list, &data);
    }

    void aListAddFrontF(List ** list, float data) {
        aListAddFront(list, &data);
    }

    void aListAddFrontC(List ** list, char data) {
        aListAddFront(list, &data);
    }

    void aListAddBeforeI(List ** list, int data) {
        aListAddBefore(list, &data);
    }

    void aListAddBeforeF(List ** list, float data) {
        aListAddBefore(list, &data);
    }

    void aListAddBeforeC(List ** list, char data) {
        aListAddBefore(list, &data);
    }

    void aListAddAfterI(List ** list, int data) {
        aListAddAfter(list, &data);
    }

    void aListAddAfterF(List ** list, float data) {
        aListAddAfter(list, &data);
    }

    void aListAddAfterC(List ** list, char data) {
        aListAddAfter(list, &data);
    }
#endif

#endif
