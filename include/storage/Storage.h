#ifndef STORAGE_H
#define STORAGE_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef STORAGE_OPTIMAL
    #define STORAGE_ARRAY_SPECIAL_CASES
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

#endif