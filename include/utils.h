#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

// Utility function to copy a string
char* copy_string(const char* str);

// Utility function to safely allocate memory
void* safe_malloc(size_t size);

// Utility function to safely free memory
void safe_free(void* ptr);

#endif
