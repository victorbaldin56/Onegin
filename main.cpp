#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "colors.h"
#include "textlib.h"
#include "sort.h"

static int tProcess(char **argv);

int main(int argc, char **argv) {
    if (argc == 1) {
        printf(FG_RED);
        printf("%s: error: no input file\n", argv[0]);
        return -1;
    }

    if (argc == 2) {
        if (!strncmp(argv[1], "--help", MAXLEN) || !strncmp(argv[1], "-h", MAXLEN)) {
            printf("Onegin -- string sorter (c) Victor Baldin, 2023\n"
                   "Usage: ./onegin [inputfile] [outputfile]\n");
            return 0;
        }

        printf(FG_RED);
        printf("%s: error: no destination file\n", argv[0]);
        return -1;
    }

    if (argc == 3) {
        //clock_t start = clock();
        
        if (tProcess(argv)) {
            return -1;
        }
        
        ///clock_t diff = clock() - start;
        //long long msec = diff * 1000 / CLOCKS_PER_SEC;
        //printf("Proceeding time %lld ms\n", msec);
        
        return 0;
    }

    if (argc > 3) {
        printf(FG_RED);
        printf("%s: error: unknown options\n", argv[0]);
        return -1;
    }
}

static int tProcess(char **argv) {
    FILE *ostream = fopen(argv[2], "w");
    char *buf = readtext(argv[1]);

    if (!buf) {
        printf(FG_RED);
        fprintf(stderr, "failed to allocate buffer\n");
        return -1;
    }

    size_t size = 0;
    Line *text = parsebuf(buf, &size); 

    fprintf(ostream, "=============PREFIX SORT=============\n");
    /*StringSort(text, START)*/;
    qsort(text, size, sizeof(Line),
            CmpStrStart);

    ON_DEBUG(printf("success sort\n"));
    
    print_text(text, size, ostream);
    fprintf(ostream, "\n=============SUFFIX SORT=============\n");

    /*StringSort(text, END)*/;
    qsort(text, size, sizeof(Line),
            CmpStrEnd);
    print_text(text, size, ostream);

    fprintf(ostream, "\n=============ORIGINAL TEXT=============\n");
    fputs(buf, ostream);

    free(buf);
    free(text);

    fclose(ostream);

    return 0;
}
