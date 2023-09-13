#include <stdio.h>
#include <assert.h>
#include "sort.h"
#include "textlib.h"

void Qsort(Data *data, bool cmpend) {
    
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
                swap(text + i, text + j);
            }
        }
    }
}

void StringSort(char **text, bool cmpend) {
    assert(text);

    while (*(text + 1)) {
        if (my_strncmp(*text, *findmin(text + 1, cmpend), MAXLEN, cmpend) > 0) {
            swap(text, findmin(text + 1, cmpend));
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
            if (*s1 != *s2) {
                return *s1 - *s2;
            }
            s1++;
            s2++;
        }
    }

    else {
        while (*s1 && *s2 && *s1 != '\n' && *s2 != '\n' && count++ < limit) {
            s1++;
            s2++;
        }

        while (*s1 && *s2 && count-- > 0) {
            if (*s1 != *s2) {
                return *s1 - *s2;
            }
            s1--;
            s2--;
        }    
    }

    return 0;
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

void swap(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
