#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
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
    assert(buf);
    int fd = open(name, O_RDONLY, 0);
    
    if (fd == -1) {
        perror("readtext");
        return NULL; 
    }

    nbytes = read(fd, buf, nbytes);
    //printf("%s\n", buf);
    return buf;
}

Line *parsebuf(char *buf, size_t *size) {
    assert(buf);
    *size = 0;

    for (char *ptr = buf; *ptr; ptr++) {
        //putchar(*ptr);
        if (*ptr == '\n' && *(ptr + 1) != '\n') {
            (*size)++;
        }
    }

    (*size)++;

    Line *text = (Line *)calloc(*size, sizeof(Line));
    assert(text);

    Line *textptr = text;
    textptr->str = buf;
    textptr++;

    while (*buf) {
        //textptr->len++;

        if (*buf == '\n' && *(buf + 1) && *(buf + 1) != '\n') {
            textptr->str = buf + 1;
            (textptr - 1)->len = buf - (textptr - 1)->str;
            ON_DEBUG(fprintf(stderr, "len = %zu", (textptr - 1)->len));
            ON_DEBUG(my_fputs((textptr - 1)->str, stderr));
            textptr++;
        }

        buf++;
    }

    assert(textptr - text - 1 < *size);

    (textptr - 1)->len = buf - (textptr - 1)->str;

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

void print_text(const Line *text, size_t size, FILE *stream) {
    assert(text);
    
    for (size_t i = 0; i < size; i++) {
        my_fputs(text[i].str, stream);
    }
}

int my_fputs(const char *s, FILE *stream) {
    assert(s);
    
    while (*s && *s != '\n') {
        fputc(*s, stream);
        s++;
    }

    fputc('\n', stream);
    return 0;
}

