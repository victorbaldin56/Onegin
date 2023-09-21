#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "sort.h"
#include "textlib.h"

void Qsort(void *data, size_t size, size_t elemsize,
           CompareFunc_t *CompareFunc) {
    //assert(arg);
    assert(data);
    assert(CompareFunc);
    size_t left  = 0;        // left pointer
    size_t right = size - 1; // right pointer

    if (!size || size == 1) {
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

void BubbleSort(char **text, bool cmpend) {
    for (size_t i = 0; *(text + i); i++) {
        for (size_t j = 0; *(text + j); j++) {
            int diff = my_strncmp(*(text + i), *(text + j), MAXLEN, cmpend);
            #ifndef NDEBUG
            printf("diff = %d\n", diff);
            my_fputs(*(text + i), stdout);
            my_fputs(*(text + j), stdout);
            #endif

            if (diff > 0) {
                strswap(text + i, text + j);
            }
        }
    }
}

void SelectSort(char **text, bool cmpend) {
    assert(text);

    while (*(text + 1)) {
        char **min = findmin(text + 1, cmpend);

        if (my_strncmp(*text, *min, MAXLEN, cmpend) > 0) {
            strswap(text, min);
        }
        
        text++;
    }
}

int my_strncmp(const char *s1, const char *s2, size_t limit, bool cmpend) {
    size_t count = 0;
    assert(s1);
    assert(s2);

    if (!cmpend) {
        while (*s1 && *s2 && *s1 != '\n' && *s2 != '\n' && count++ < limit) {
            if (!isalpha(*s1)) {
                s1++;
            }

            if (!isalpha(*s2)) {
                s2++;
            }

            if (!(*s1) || !(*s2)) {
                return 0;
            }
            
            if (*s1 != *s2) {
                return *s1 - *s2;
            }

            s1++;
            s2++;
        }
    }

    else {
        size_t count1 = 0;
        size_t count2 = 0;

        while (*s1 && *s1 != '\n' && count1++ < limit) {
            s1++;
        }

        while (*s2 && *s2 != '\n' && count2++ < limit) {
            s2++;
        }

        while (count1 && count2) {
            if (!isalpha(*s1)) {
                s1--;
                count1--;
            }

            if (!isalpha(*s2)) {
                s2--;
                count2--;
            }

            if (!count1 || !count2) {
                return 0;
            }
            
            if (*s1 != *s2) {
                return *s1 - *s2;
            }
            
            s1--;
            count1--;
            count2--;
            s2--;
        }    
    }

    return 0;
}

int CmpStrStart(const void *a, const void *b) {
    assert(a);
    assert(b);
    const char *s1 = *((const char **)a);
    const char *s2 = *((const char **)b);

    assert(s1);
    assert(s2);

    //size_t limit = *((const size_t *)arg);
    //assert(LenStr(s1) < limit);
    //assert(LenStr(s2) < limit);
    size_t count = 0;

    while (*s1 && *s2 && *s1 != '\n' && *s2 != '\n') {
        while (!isalpha(*s1) && *s1 && *s1 != '\n') {
            s1++;
        }

//        assert(count < limit);

        while (!isalpha(*s2) && *s2 && *s2 != '\n') {
            s2++;
        }

//        assert(count < limit);
        
        if (*s1 != *s2) {
            return *s1 - *s2;
        }

        s1++;
        s2++;
    }

//    assert(count < limit);

    return 0;
}

int CmpStrEnd(const void *a, const void *b) {
    assert(a);
    assert(b);
    const char *s1 = *((const char **)a);
    const char *s2 = *((const char **)b);
//    const size_t limit = *((const size_t *)arg);
    size_t count1 = 0;
    size_t count2 = 0; // Srazy s nazaada

    while (*s1 && *s1 != '\n') {
        s1++;
        count1++;
    }

    while (*s2 && *s2 != '\n') {
        s2++;
        count2++;
    }

    while (count1 && count2) {
        while (count1 && !isalpha(*s1)) {
            s1--;
            count1--;
        }

        while (count2 && !isalpha(*s2)) {
            s2--;
            count2--;
        }

        if (!count1 || !count2) {
            return 0;
        }
        
        if (*s1 != *s2) {
            return *s1 - *s2;
        }

        count1--;
        count2--;
        s1--;
        s2--;
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

char **findmin(char **text, bool cmpend) {
    char **min = text;

    while (*text) {
        if (my_strncmp(*text, *min, MAXLEN, cmpend) < 0) {
            min = text;
        }
        
        text++;
    }

    return min;
}

void strswap(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void Swap(void *data, size_t i, size_t j, size_t elemsize) {
    assert(data);

    for (size_t count = 0; count < elemsize; count++) {
        char tmp = *(char *)(data + i * elemsize + count);
        *(char *)(data + i * elemsize + count) = *(char *)(data + j * elemsize + count);
        *(char *)(data + j * elemsize + count) = tmp;
    }
}
