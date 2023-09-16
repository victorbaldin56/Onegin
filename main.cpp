#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "textlib.h"
#include "text_process.h"
#include "sort.h"

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
        
        tProcess(argc, argv);
        
        clock_t diff = clock() - start;
        long long msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("Proceeding time %lld ms\n", msec);
        
        return 0;
    }
}
