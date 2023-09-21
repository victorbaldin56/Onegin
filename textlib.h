#ifndef TEXTLIB
#define TEXTLIB
//#define NDEBUG

#include <unistd.h>
#include <sys/types.h>

#define PERMS 0666


#define NDEBUG

#ifndef NDEBUG
#define ON_DEBUG(x) x
#else
#define ON_DEBUG(x)
#endif

const size_t MAXLEN = 100000; // max str len

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
char **parsebuf(char *buf, size_t *size);

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
void print_text(char **text, FILE *stream); 

#endif // TEXTLIB
