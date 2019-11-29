/* file =  mydefs.h */
/* these are things that are probably defined properly in some .h file,
   but for now I just define them myself here */
#define FALSE 0
#define TRUE 1

#include <strings.h>
#include <stdio.h>
#include <sys/time.h>
#include <ctype.h>

void perror(const char *s);
int printf(const char *format, ...); 
int fprintf(FILE *stream, const char *format, ...);  
int fclose(FILE *stream);
int sscanf(const char *s, const char *format, ...);

int rand(void);

unsigned int alarm(unsigned int seconds);

/* int gettimeofday(struct timeval *tp, struct timezone *tzp);*/




/* char tolower(char c); */

void usleep(unsigned useconds); 
int getpid(void);

char *getlogin(void);

/* void system(char *string); */

double drand48(void);
void srand48(long seedval);
