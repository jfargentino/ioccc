#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int _int_mul (int x0, ...) {
    va_list x_list;
    int y = x0;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while (xk != 0) {
        y *= xk;
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
#define int_mul(...) _int_mul(__VA_ARGS__, 0)

static int _int_print (char sep, int x0, ...) {
    va_list x_list;
    int y = printf ("%+9d", x0);
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while (xk < INT_MAX) {
        y += printf ("%c%+9d", sep, xk);
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
#define int_print(...) _int_print(__VA_ARGS__, INT_MAX)

static int _int_max (int x0, ...) {
    va_list x_list;
    int y = x0;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while (xk < INT_MAX) {
        if (xk > y) {
            y = xk;
        }
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
#define int_max(...) _int_max(__VA_ARGS__, INT_MAX)

static int _int_min (int x0, ...) {
    va_list x_list;
    int y = x0;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while (xk > INT_MIN) {
        if (xk < y) {
            y = xk;
        }
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
#define int_min(...) _int_min(__VA_ARGS__, INT_MIN)

static int _int_sum (int x0, ...) {
    va_list x_list;
    int y = x0;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while ((xk > INT_MIN) && (xk < INT_MAX)) {
        y += xk;
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
#define int_sum(...) _int_sum(__VA_ARGS__, INT_MAX)

static size_t _int_size (int x0, ...) {
    size_t k = 0;
    if (x0 == INT_MAX) {
        return k;
    }
    k ++;
    va_list x_list;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while (xk < INT_MAX) {
        k ++;
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return k;
}
#define int_size(...) _int_size(__VA_ARGS__, INT_MAX)

static int _int_mean (int x0, ...) {
    va_list x_list;
    int y = x0;
    size_t k = 1;
    va_start(x_list, x0);
    int xk = va_arg(x_list, int);
    while ((xk > INT_MIN) && (xk < INT_MAX)) {
        y += xk;
        k ++;
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y / k;
}
#define int_mean(...) _int_mean(__VA_ARGS__, INT_MAX)

static int _int_sum2 (int xend, ...) {
    va_list x_list;
    int y = 0;
    va_start(x_list, xend);
    int xk = va_arg(x_list, int);
    while (xk != xend) {
        y += xk;
        xk = va_arg(x_list, int);
    }
    va_end(x_list);
    return y;
}
//#define __int_sum(xend, ...) _int_sum2(xend, __VA_ARGS__, xend)
//#define int_sum(...) __int_sum(INT_MAX, __VA_ARGS__)

#define int_check(...) printf("[ ");                                         \
                       int_print(' ', __VA_ARGS__);                          \
                       printf(" ]:%zu\n", int_size(__VA_ARGS__));            \
                       printf( "sum=%d, mul=%d, min=%d, max=%d, mean=%d\n\n",\
                               int_sum(__VA_ARGS__), int_mul(__VA_ARGS__),   \
                               int_min(__VA_ARGS__), int_max(__VA_ARGS__),   \
                               int_mean(__VA_ARGS__)                         )

static size_t vad (size_t nb, ...) {
    va_list x_list;
    va_start(x_list, nb);
    size_t k = 0;
    while (k < nb) {
        k++;
        uint32_t x = va_arg(x_list, uint32_t);
        char c = '\0';
        //printf ("%08X%c", x, (k%4 == 0) ? '\n' : ' ');
        printf ("%08X", x);
        if (k%4 == 0) {
            c = '\n';
        } else {
            c = ' ';
        }
        printf ("%c", c);
    }
    va_end(x_list);
    return k;
}

int main (int argc, char ** argv) {
    int_check (0);
    int_check (1, 1);
    int_check (2, 1, 1);
    int_check (1, 2, 3);
    int_check (111, 231, 394);
    for (int k = 1;  k < argc; k++) {
        vad(atoi(argv[k]));
    }
    vad(8);
    return argc;
}

