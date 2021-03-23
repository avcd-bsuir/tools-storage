// License: CC BY-NC-SA 4.0
/*
 * Array.h
 *
 * C++'s vector-like array implementation.
 *
 * Written by AlexeyFilich
 * 23 mar 2021
 */

#ifndef ARRAY_H
#define ARRAY_H

#ifdef STORAGE_ARRAY_USE_INDEXES
    #define aArrayDump(type, array, format) \
        for (int i = 0; i < array.size; i++) \
            printf(format, i, *(type *)aArrayGet(&array, i))
#else
    #define aArrayDump(type, array, format) \
        for (int i = 0; i < array.size; i++) \
            printf(format, *(type *)aArrayGet(&array, i))
#endif

#define MEMADDR(index) \
    (char *)array->data + (index * array->element_size)

#define GROW_IF_NEEDED(array) \
    if (!array->avaliable) { \
        void * old = array->data; \
        if ((array->data = calloc(array->size + 1, array->element_size)) == NULL) RETURN_1; \
        memcpy(array->data, old, array->size * array->element_size); \
        array->avaliable++; \
        free(old); \
    }

typedef struct Array {
    size_t size; // Number of elements
    size_t avaliable; // Number of free positions in currently allocated memory
    size_t element_size; // Size of element used in array
    void * data; // Array pointer
} Array;

#define aArrayInit(array, size, type) \
    aArrayInitType(array, size, sizeof(type));

int aArrayInitType(Array * array, size_t size, size_t element_size) {
    if (array == NULL) RETURN_1;
    size = (size > 0) ? size : 0; // Set size to 0 if it less than 0
    array->avaliable = (size_t)0; // No free spaces
    array->data = calloc(size, element_size); // Allocate and set to 0
    array->element_size = element_size; // Size of each element in an array
    array->size = size; // Array size in elements
    if (array->data != NULL) // Return NULL if calloc was unsuccessfull
        return 0;
    else
        RETURN_1;
}

int aArraySet(Array * array, size_t index, void * element) {
    if (array == NULL || element == NULL || index >= array->size) RETURN_1;
    memcpy(MEMADDR(index), element, array->element_size); // Copy to address START + INDEX * ELEMENT_SIZE element with set size
    return 0;
}

int aArrayPush(Array * array, void * element) {
    if (array == NULL || element == NULL) RETURN_1;
    GROW_IF_NEEDED(array); // Add 1 empty spot if there are none
    array->size++;
    array->avaliable--;
    return aArraySet(array, array->size - 1, element); // Push element to the last element
}

int aArrayInsert(Array * array, size_t index, void * element) {
    if (array == NULL || element == NULL || array->element_size == 0 || index > array->size) RETURN_1;
    GROW_IF_NEEDED(array); // Add 1 empty spot if there are none
    array->size++;
    array->avaliable--;
    memmove(MEMADDR(index) + array->element_size, MEMADDR(index), (array->size - index) * array->element_size); // Move all elements starting from index to the right
    return aArraySet(array, index, element); // Set element to an index
}

#ifdef STORAGE_SPECIAL_CASES
    int aArraySetI(Array * array, size_t index, int element) {
        return aArraySet(array, index, &element);
    }

    int aArraySetF(Array * array, size_t index, float element) {
        return aArraySet(array, index, &element);
    }

    int aArrayPushI(Array * array, int element) {
        return aArrayPush(array, &element);
    }

    int aArrayPushF(Array * array, float element) {
        return aArrayPush(array, &element);
    }

    int aArrayInsertI(Array * array, size_t index, int element) {
        return aArrayInsert(array, index, &element);
    }

    int aArrayInsertF(Array * array, size_t index, float element) {
        return aArrayInsert(array, index, &element);
    }
#endif

#define aArrayGetAs(array, index, type) \
    *(type *)aArrayGet(array, index)

void * aArrayGet(Array * array, size_t index) {
    if (array == NULL || index >= array->size) RETURN_NULL;
    return MEMADDR(index); // Return data at address START + INDEX * ELEMENT_SIZE
}

#define aArrayPopAs(array, type) \
    *(type *)aArrayPop(array)

void * aArrayPop(Array * array) {
    if (array == NULL || array->size <= 0) RETURN_NULL;
    array->size--;
    array->avaliable++;
    return MEMADDR(array->size); // Return last element
}

int aArrayRemove(Array * array, size_t index) {
    if (array == NULL || array->element_size == 0 || index >= array->size) RETURN_1;
    memmove(MEMADDR(index), MEMADDR(index) + array->element_size, (array->size - index - 1) * array->element_size); // Move all elements starting from index + 1 to the left
    array->size--;
    array->avaliable++;
    return 0;
}

void aArrayDestroy(Array * array) {
    free(array->data);
}

#endif
