#ifndef SORT
#define SORT

#include <stdio.h>

typedef int CompareFunc_t(const void *a, const void *b);

/**
 * 
*/
int CmpStrStart(const void *s1, const void *s2);

/**
 * 
*/
int CmpStrEnd(const void *s1, const void *s2); 

/**
 * 
*/
void Qsort(void *data, size_t size, size_t elemsize, 
           CompareFunc_t *CompareFunc);

void Swap(void *data, size_t i, size_t j, size_t elemsize);

#endif // SORT