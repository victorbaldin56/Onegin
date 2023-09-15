#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textlib.h"
#include "sort.h"

void tProcess(int argc, char **argv) {
    remove("output.txt");
        FILE *ostream = fopen("output.txt", "a");
        char *buf = readtext(argv[1]);

        if (!buf) {
            exit(1);
        }

        #ifndef NDEBUG
        //printf("main: call parsebuf\n");
        #endif

        size_t size = 0;
        char **text = parsebuf(buf, &size); 

        size_t limit = MAXLEN;
        /*StringSort(text, START)*/;
        qsort_r(text, size, sizeof(char *),
                CmpStrStart, &limit);
        #ifndef NDEBUG
        //printf("success sort\n");
        #endif
        print_text(text, ostream);

        /*StringSort(text, END)*/;
        qsort_r(text, size, sizeof(char *),
                CmpStrEnd, &limit);
        print_text(text, ostream);

        fputs(buf, ostream);

        free(buf);
        free(text);

        fclose(ostream);
}