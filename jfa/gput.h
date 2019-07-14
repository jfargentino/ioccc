#ifndef GPUT_H
#define GPUT_H

#include <stdio.h>

/** Primitive to spit out an unsigned long long on given base ****************/
static int ullput(unsigned long long x, int base, FILE * stream) {
    unsigned long long y = 1ull;
    while (x >= y * base) {
        // x == 0 => y == 1 since still 1 digit to display
        y *= base;
    }
    int k = 0;
    while (y > 0ull) {
        int digit = x / y;
        if (digit < 10) {
            fputc(digit+'0', stream);
        } else {
            fputc((digit-10)+'a', stream);
        }
        k ++;
        x -= digit * y;
        y /= base;
    }
    return k;
}

/* Primitive to spit out a signed long long on given base ********************/
static int llput(long long x, int base, FILE * stream) {
    int k = 0;
    if (x < 0ll) {
        fputc ('-', stream);
        k ++;
        x = -x;
    }
    return k + ullput(x, base, stream);
}

/* Primitive to spit out a floating double precision with given digits nb ****/
static int ldput(long double x, int res, FILE * stream) {
    int k = 0;
    if (x < 0.0l) {
        fputc ('-', stream);
        k ++;
        x = -x;
    }
    int e = 0;
    while (x < 1.0l) {
        e --;
        x *= 10.0l;
    }
    while (x > 10.0l) {
        e ++;
        x /= 10.0l;
    }
    int r = x;
    fputc('0' + r, stream);
    k ++;
    x -= r;
    fputc('.', stream);
    k ++;
    while (res > 0) {
        x *= 10.0l;
        r = x;
        fputc('0' + r, stream);
        k ++;
        x -= r;
        res --;
    }
    if (e != 0) {
        fputc('e', stream);
        k ++;
        k += llput(e, 10, stream);
    }
    return k;
}

// just to harmonize arguments /////////////////////////////////////////////////
// if defined as macros, compilation error
static int bin(unsigned long long x, FILE * stream) {
    return ullput(x, 2, stream);
}

static int udec(unsigned long long x, FILE * stream) {
    return ullput(x, 10, stream);
}

static int idec(long long x, FILE * stream) {
    return llput(x, 10, stream);
}

static int hex(unsigned long long x, FILE * stream) {
    return ullput(x, 16, stream);
}

// using hex for pointer trig a warning
static int ptr(void const * x, FILE * stream) {
    return ullput((unsigned long long)x, 16, stream);
}

static int sci3(float x, FILE * stream) {
    return ldput(x, 3, stream);
}

static int sci6(double x, FILE * stream) {
    return ldput(x, 6, stream);
}

static int sci9(long double x, FILE * stream) {
    return ldput(x, 9, stream);
}

// a generic put //////////////////////////////////////////////////////////////
#define gput(x, stream) _Generic( (x),                        \
                                  _Bool              : bin,   \
                                  char *             : fputs, \
                                  char const *       : fputs, \
                                  signed char        : idec,  \
                                  short              : idec,  \
                                  int                : idec,  \
                                  long               : idec,  \
                                  long long          : idec,  \
                                  unsigned char      : hex,   \
                                  unsigned short     : hex,   \
                                  unsigned int       : udec,  \
                                  unsigned long      : udec,  \
                                  unsigned long long : udec,  \
                                  float              : sci3,  \
                                  double             : sci6,  \
                                  long double        : sci9,  \
                                  void *             : ptr,   \
                                  void const *       : ptr,   \
                                  default: hex ) ((x), stream)
///////////////////////////////////////////////////////////////////////////////

#endif // GPUT_H

