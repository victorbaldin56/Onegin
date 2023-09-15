#ifndef SORT
#define SORT

#include <stdio.h>

#define MIN(x, y) (x < y? x : y)

const bool START = 0; // sort starting by the beginning of strings
const bool END   = 1; // sort starting by the end of strings

typedef int CompareFunc_t(const void *a, const void *b, void *arg);

/**
 * 
*/
int CmpStrStart(const void *s1, const void *s2, void *limit);

/**
 * 
*/
int CmpStrEnd(const void *s1, const void *s2, void *limit); 

/**
 * 
*/
int my_strncmp(const char *s1, const char *s2, size_t limit, bool cmpend);

/**
 * 
*/
void SelectSort(char **text, bool cmpend);

/**
 * 
*/
void BubbleSort(char **text, bool cmpend);

/**
 * 
*/
void Qsort(void *data, size_t size, size_t elemsize, 
           CompareFunc_t *CompareFunc, void *arg);

/**
 * 
*/
char **findmin(char **text, bool cmpend);

/**
 * 
*/
void strswap(char **a, char **b);

void Swap(void *a, void *b, size_t elemsize);

#endif // SORT