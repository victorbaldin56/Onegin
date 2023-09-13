#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textlib.h"
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
        
        remove("output.txt");
        FILE *ostream = fopen("output.txt", "a");
        char *buf = readtext(argv[1]);

        if (!buf) {
            return -1;
        }

        printf("main: call parsebuf\n");

        char **text = parsebuf(buf);

        BubbleSort(text, START);
        #ifndef NDEBUG
        printf("success sort\n");
        #endif
        print_text(text, ostream);

        BubbleSort(text, END);
        print_text(text, ostream);

        fputs(buf, ostream);

        free(buf);
        free(text);
        
        return 0;
    }
}
