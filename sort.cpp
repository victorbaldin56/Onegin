#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "sort.h"
#include "textlib.h"

void Qsort(void *data, size_t size, size_t elemsize,
           CompareFunc_t *CompareFunc, void *arg) {
    assert(arg);
    assert(data);
    assert(CompareFunc);
    char *left  = (char *)data;                         // left pointer
    char *right = (char *)data + (size - 1) * elemsize; // right pointer
    
    char *end = right;

    assert(*left);
    assert(*right);

    if (size == 1) {
        return;
    }

    if (size == 2) {
        assert(end);
        assert(data);
        assert(arg);

        if ((*CompareFunc)(data, end, arg) > 0) {
            Swap(data, end, elemsize);
            return;
        }
    }

    void *pivot = calloc(1, elemsize);
    assert(pivot);
    char *mid = (char *)data + (size / 2) * elemsize;

    memcpy(pivot, mid, elemsize); // copy pivot element
    
    assert(end);

    printf("starting partitioner\n");

    while (left < right) {
        assert(*left);
        assert(arg);
        assert(*right);
        
        while (left < end && (*CompareFunc)(left, pivot, arg) < 0) {
            assert(left);
            printf("bad element found: %p", left);
            left += elemsize;
        }

        printf("left = %p\n", left);

        //printf("stop left\n");

        while (right > (char *)data && (*CompareFunc)(right, pivot, arg) > 0) {
            assert(right);
            right -= elemsize;
        }

        printf("right = %p\n", right);

        //printf("stop right\n");

        //printf("left = %c, right = %c\n", *left, *right);
        Swap(left, right, elemsize);
        //printf("left = %c, right = %c\n", *left, *right);
    }

    printf("success partitioner\n");

    Qsort(left, (left - (char *)data) / elemsize, elemsize,
          CompareFunc, arg);

    Qsort(right, (end - right) / elemsize, elemsize,
          CompareFunc, arg);

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

void StringSort(char **text, bool cmpend) {
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

int CmpStrStart(const void *a, const void *b, void *arg) {
    assert(a);
    assert(b);
    const char *s1 = *((const char **)a);
    const char *s2 = *((const char **)b);

    if (!s1 || !s2) {
        printf("found NULL!!!!\n");
        exit(1);
    } 

    size_t limit = *((const size_t *)arg);
    //assert(LenStr(s1) < limit);
    //assert(LenStr(s2) < limit);
    size_t count = 0;

    while (*s1 && *s2 && *s1 != '\n' && *s2 != '\n' && count++ < limit) {
        while (!isalpha(*s1) && *s1 && *s1 != '\n') {
            s1++;
        }

        assert(count < limit);

        while (!isalpha(*s2) && *s2 && *s2 != '\n') {
            s2++;
        }

        assert(count < limit);
        
        if (*s1 != *s2) {
            return *s1 - *s2;
        }

        s1++;
        s2++;
    }

    assert(count < limit);

    return 0;
}

int CmpStrEnd(const void *a, const void *b, void *arg) {
    assert(a);
    assert(b);
    const char *s1 = *((const char **)a);
    const char *s2 = *((const char **)b);
    const size_t limit = *((const size_t *)arg);
    size_t count1 = 0;
    size_t count2 = 0;

    while (*s1 && *s1 != '\n' && count1++ < limit) {
        s1++;
    }

    while (*s2 && *s2 != '\n' && count2++ < limit) {
        s2++;
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

void Swap(void *a, void *b, size_t elemsize) {
    void *tmp = calloc(1, elemsize);
    assert(tmp);
    memcpy(tmp, a, elemsize);
    memcpy(a, b, elemsize);
    memcpy(b, tmp, elemsize);
    free(tmp);
    tmp = NULL;
}
