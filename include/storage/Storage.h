// License: CC BY-NC-SA 4.0
/*
 * Storage.h
 *
 * Master include file. Processes some defines for Array and includes necessary libraries.
 *
 * Written by AlexeyFilich
 * 17 mar 2021
 */

#ifndef STORAGE_H
#define STORAGE_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef STORAGE_OPTIMAL
    #define STORAGE_SPECIAL_CASES
    #define STORAGE_ARRAY_USE_INDEXES
    #define STORAGE_EXIT_ON_FAILURE
#endif

#ifdef STORAGE_EXIT_ON_FAILURE
    #define RETURN_1 exit(1)
    #define RETURN_NULL exit(1)
#else
    #define RETURN_1 return 1
    #define RETURN_NULL return NULL
#endif

#include "Array.h"
#include "Stack.h"

#endif
