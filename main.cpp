#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "textlib.h"
#include "sort.h"

static int tProcess(int argc, char **argv);

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("%s: error: no input files\n"
               "Hint: use --help or -h option to see the usage guide\n", argv[0]);
        return -1;
    }

    if (argc >= 2) {
        if (!strncmp(argv[1], "--help", MAXLEN) || !strncmp(argv[1], "-h", MAXLEN)) {
            printf("Onegin -- string mixer (c) Victor Baldin\n"
                "Usage: ./onegin [options]\n"
                "Options:\n"
                "\t -o FILE");
            return 0;
        }
        
        clock_t start = clock();
        
        if (tProcess(argc, argv)) {
            fprintf(stderr, "failed to allocate buffer\n");
            return -1;
        }
        
        clock_t diff = clock() - start;
        long long msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Proceeding time %lld ms\n", msec);
        
        return 0;
    }
}

static int tProcess(int argc, char **argv) {
    FILE *ostream = fopen("output.txt", "w");
    char *buf = readtext(argv[1]);

    if (!buf) {
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
