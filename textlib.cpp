#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include "textlib.h"
#include "sort.h"

char *readtext(char *name) {
    assert(name);
    size_t nbytes = fsize(name);
    char *buf = (char *)calloc(nbytes + 1, sizeof(char));
    int fd = open(name, O_RDONLY, 0);
    
    if (fd == -1) {
        perror("");
        return NULL; 
    }

    read(fd, buf, nbytes);
    printf("%s\n", buf);
    return buf;
}

char **parsebuf(char *buf) {
    assert(buf);
    size_t count = 1;

    for (char *ptr = buf; *ptr; ptr++) {
        //putchar(*ptr);
        if (*ptr == '\n') {
            count++;
        }
    }

    char **text = (char **)calloc(count + 1, sizeof(char *));
    assert(text);
    char **txtptr = text;

    while (*buf) {
        if (*buf == '\n') {
            #ifndef NDEBUG
            printf("\\n found on the address %p\n", buf);     
            #endif
            if (*(buf + 1)) {
                *txtptr++ = buf + 1;
            }
        }

        buf++;
    }

    return text;
}

off_t fsize(char *name) {
    assert(name);
    struct stat stbuf = {};
    
    if (stat(name, &stbuf) == -1) {
        return -1;
    }

    return stbuf.st_size;
}

void print_text(char **text, FILE *stream) {
    while (*text) {
        my_fputs(*text, stream);
        text++;
    }
    
    fprintf(stream, "\n====================================\n");
}

int my_fputs(const char *s, FILE *stream) {
    while (*s && *s != '\n') {
        fputc(*s, stream);
        s++;
    }

    fputc('\n', stream);
    return 0;
}
