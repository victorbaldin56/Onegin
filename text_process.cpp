#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textlib.h"
#include "sort.h"

#ifndef NDEBUG
#define ON_DEBUG(x) x
#else
#define ON_DEBUG(x)
#endif

void tProcess(int argc, char **argv) {
    FILE *ostream = fopen("output.txt", "w");
    char *buf = readtext(argv[1]);

    if (!buf) {
        fprintf(stderr, "failed to allocate buffer\n");
        exit(1);
    }

    size_t size = 0;
    char **text = parsebuf(buf, &size); 

    size_t limit = MAXLEN;
    /*StringSort(text, START)*/;
    Qsort(text, size - 1, sizeof(char *),
            CmpStrStart, &limit);

    ON_DEBUG(printf("success sort\n"));
    
    print_text(text, ostream);

    /*StringSort(text, END)*/;
    Qsort(text, size - 1, sizeof(char *),
            CmpStrEnd, &limit);
    print_text(text, ostream);

    fputs(buf, ostream);

    free(buf);
    free(text);

    fclose(ostream);
}