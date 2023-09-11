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
off_t fsize(char *name);

/**
 * 
*/
char *readtext(char *name);

/**
 * 
*/
char **parsebuf(char *buf);

/**
 * 
*/
int my_fputs(const char *s, FILE *stream);

/**
 * 
*/
void print_text(char **text, FILE *stream); 

#endif // TEXTLIB
