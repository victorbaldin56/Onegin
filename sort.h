#ifndef SORT
#define SORT

#include <stdio.h>

const bool START = 0; // sort starting by the beginning of strings
const bool END   = 1; // sort starting by the end of strings

typedef int CompareFunc_t(const void *a, const void *b, const bool cmpend);

/**
 * 
*/
typedef struct {
    void *arr;
    size_t size;
    size_t elemsize;
    CompareFunc_t *CompareFunc;
} Data;

/**
 * 
*/
int my_strncmp(const char *s1, const char *s2, size_t limit, bool cmpend);

/**
 * 
*/
void StringSort(char **text, bool cmpend);

/**
 * 
*/
void Qsort(Data *data, bool cmpend);

/**
 * 
*/
char **findmin(char **text, bool cmpend);

/**
 * 
*/
void swap(char **a, char **b);

#endif // SORT