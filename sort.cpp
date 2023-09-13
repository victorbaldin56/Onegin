#include <stdio.h>
#include <assert.h>
#include <ctype.h>
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
        char **min = findmin(text + 1, cmpend);

        if (my_strncmp(*text, *min, MAXLEN, cmpend) > 0) {
            swap(text, min);
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

        while (count1-- && count2--) {
            if (!isalpha(*s1)) {
                s1--;
                count1--;
            }

            if (!isalpha(*s2)) {
                s2--;
                count2--;
            }

            if (!count) {
                return 0;
            }
            
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
