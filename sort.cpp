#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "sort.h"
#include "textlib.h"

void Qsort(void *data, size_t size, size_t elemsize,
           CompareFunc_t *CompareFunc) {
    assert(data);
    assert(CompareFunc);
    size_t left  = 0;        // left pointer
    size_t right = size - 1; // right pointer
    assert(size < INT_MAX);

    if (size <= 1) {
        return;
    }

    if (size == 2) {
        if ((*CompareFunc)(data, data + right * elemsize) > 0) {
            Swap(data, left, right, elemsize);
        }

        return;
    }

    void *pivot = calloc(1, elemsize);
    assert(pivot);
    char *mid = (char *)data + (size / 2) * elemsize;

    memcpy(pivot, mid, elemsize); // copy pivot element

    ON_DEBUG(("starting partitioner\n"
              "SIZE = %zu\n", size));

    while (left < right) {
        while (left < size - 1 && (*CompareFunc)(data + left * elemsize, pivot) < 0) {
            //printf("bad element found: %p", left);
            ON_DEBUG(("left = %zu\n", left));
            left++;
        }

        ON_DEBUG(("bad element: left = %zu\n", left));

        //printf("stop left\n");

        while (right > 1 && (*CompareFunc)(data + right * elemsize, pivot) > 0) {
            ON_DEBUG(("right = %zu\n", right));
            right--;
        }

        ON_DEBUG(("bad element: right = %zu\n", right));

        //printf("stop right\n");

        //printf("left = %c, right = %c\n", *left, *right);
        Swap(data, left, right, elemsize);
        //printf("left = %c, right = %c\n", *left, *right);
        
        assert(right > 0);
        assert(left < size);
        left++;
        right--;
    }

    ON_DEBUG(("success partitioner\n"));

    Qsort(data, right, elemsize,
          CompareFunc);

    Qsort(data + right * elemsize, size - left, elemsize,
          CompareFunc);

    free(pivot);
    pivot = NULL;
}

int CmpStrStart(const void *a, const void *b) {
    assert(a);
    assert(b);
    Line s1 = *(const Line *)a;
    Line s2 = *(const Line *)b;

    assert(s1.str);
    assert(s2.str);

    while (*s1.str && *s2.str && *s1.str != '\n' && *s2.str!= '\n') {
        if (!isalpha(*s1.str) && *s1.str && *s1.str != '\n') {
            s1.str++;
            continue;
        }

        if (!isalpha(*s2.str) && *s2.str && *s2.str != '\n') {
            s2.str++;
            continue;
        }
        
        if (*s1.str != *s2.str) {
            return *s1.str - *s2.str;
        }

        s1.str++;
        s2.str++;
    }

    return 0;
}

int CmpStrEnd(const void *a, const void *b) {
    assert(a);
    assert(b);
    Line s1 = *(const Line *)a;
    Line s2 = *(const Line *)b;
    
    const char *start1 = s1.str, *start2 = s2.str;
    s1.str += s1.len;
    s2.str += s2.len;

    while (s1.str >= start1 && s2.str >= start2) {
        if (s1.str >= start1 && !isalpha(*s1.str)) {
            s1.str--;
            continue;
        }

        if (s2.str >= start2 && !isalpha(*s2.str)) {
            s2.str--;
            continue;
        }
        
        if (*s1.str != *s2.str) {
            return *s1.str - *s2.str;
        }

        s1.str--;
        s2.str--;
    }

    return 0;    
}

size_t LenStr(const char *s) {
    size_t count = 0;

    for (; *s && *s != '\n'; s++) {
        count++;    
    }

    return count;
}

void Swap(void *data, size_t i, size_t j, size_t elemsize) {
    assert(data);

    for (size_t count = 0; count < elemsize; count++) {
        char tmp = *(char *)(data + i * elemsize + count);
        *(char *)(data + i * elemsize + count) = *(char *)(data + j * elemsize + count);
        *(char *)(data + j * elemsize + count) = tmp;
    }
}
