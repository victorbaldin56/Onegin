#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textlib.h"
#include "text_process.h"
#include "sort.h"

void tProcess(int argc, char **argv) {
    FILE *ostream = fopen("output.txt", "w");
    char *buf = readtext(argv[1]);

    if (!buf) {
        fprintf(stderr, "failed to allocate buffer\n");
        exit(1);
    }

    size_t size = 0;
    Line *text = parsebuf(buf, &size); 

    fprintf(ostream, "=============PREFIX SORT=============\n");
    /*StringSort(text, START)*/;
    Qsort(text, size - 1, sizeof(Line),
            CmpStrStart);

    ON_DEBUG(printf("success sort\n"));
    
    print_text(text, ostream);
    fprintf(ostream, "\n=============SUFFIX SORT=============\n");

    /*StringSort(text, END)*/;
    qsort(text, size - 1, sizeof(Line),
            CmpStrEnd);
    print_text(text, ostream);

    fprintf(ostream, "\n=============ORIGINAL TEXT=============\n");
    fputs(buf, ostream);

    free(buf);
    free(text);

    fclose(ostream);
}