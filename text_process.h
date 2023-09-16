#ifndef TEXTPROCESS
#define TEXTPROCESS

#define NDEBUG

#ifndef NDEBUG
#define ON_DEBUG(x) x
#else
#define ON_DEBUG(x)
#endif

void tProcess(int argc, char **argv);

#endif 