#include <stdio.h>

#define CHECK_GZ(x) ( int __x__ = (x),                  \
                      __x__ > 0 ? printf(  ">0\n")  \
                                : printf(  "<=0\n"),\
                      __x__ )

char a[3] = { '^' , '~', '|' };
char b[3] = { '\'', '-', '!' };

int main (void) {

    // -mrdrnd
    unsigned int rd;
    unsigned int rdret = _builtin_ia32_rdrand32_step (&rd);
    printf ("%u %u\n", rdret, rd);

  /*
    int y = 5;
    int z = CHECK_GZ(y);
    char c = a[0] ^ b[1];
    char d = a[2] | b[0];
    char e = ~a[1];
    printf ("y = %d\n", CHECK_GZ(y));
    printf ("z = %d\n", CHECK_GZ(z));
    return 0;
    */
}

