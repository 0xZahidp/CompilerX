#include "utils.h"
#include <string.h>

// Safe memory allocation
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    return ptr;
}

// Safe free memory
void safe_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

// Copy a string and return a new allocated memory
char* copy_string(const char* str) {
    char* copy = (char*)safe_malloc(strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}
