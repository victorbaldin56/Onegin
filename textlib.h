#ifndef TEXTLIB
#define TEXTLIB
//#define NDEBUG

#include <unistd.h>
#include <sys/types.h>

#define PERMS 0666

const size_t MAXLEN = 100000; // max str len

/**
 * 
*/
typedef struct {
    const char *str;
    size_t len;
} Line;

/**
 * 
*/
off_t fsize(char *name);

/**
 * 
*/
char *readtext(char *name);

/**
 * 
*/
Line *parsebuf(char *buf, size_t *size);

/**
 * 
*/
int my_fputs(const char *s, FILE *stream);

/**
 * 
*/
size_t LenStr(const char *s);

/**
 * 
*/
void print_text(const Line *text, FILE *stream); 

#endif // TEXTLIB
