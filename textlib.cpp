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

    char *orig_buf = buf;

    for (char *ptr = buf; *ptr; ptr++) {
        //putchar(*ptr);
        if (*ptr == '\n' && *(ptr + 1) != '\n') {
           // if (isLetterStr(ptr + 1)) {
                (*size)++;
           // }
        }
    }

    Line *text = (Line *)calloc(*size + 2, sizeof(Line));
    assert(text);

    Line *textptr = text;

    while (*buf) {
        //textptr->len++;

        if (*buf == '\n' && *(buf + 1) && *(buf + 1) != '\n') {
//            if (isLetterStr(buf + 1)) {
                textptr->str = buf + 1;
//          }
            //textptr->len = (textptr + 1)->str - (textptr)->str;

            /*ifr(textptr->str) {
                my_fputs(textptr->str, stdout);
            }*/

            //printf("len = %zu\n", textptr->len);
            textptr++;
        }

        buf++;
    }

    text->len = text->str - orig_buf;

    for (textptr = text + 1; textptr < text + *size; textptr++) {
        textptr->len = textptr->str - (textptr-1)->str;
        /*fprintf(stderr, "len = %d", textptr->len);
        my_fputs(textptr->str, stderr);*/
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

void print_text(const Line *text, FILE *stream) {
    assert(text);
    
    while (text->str) {
        my_fputs(text->str, stream);
        text++;
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

bool isLetterStr(const char *s) {
    assert(s);

    while (*s != '\n' && *s) {
        if (isalpha(*s)) {
            return 1;
        }
    }

    ON_DEBUG((stderr, "isLetterStr success\n"));
    return 0;
}
