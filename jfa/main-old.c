#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

////////////////////////////////////////////////////////////////////////////////
// at the end,
// if sum == 2;
//     sum = 1;
// fi
// if sum == 1
//     1 or 11
// else
//     sum
// fi
////////////////////////////////////////////////////////////////////////////////
#if !defined (INTROSPECT)
#   define INTROSPECT 0
#endif

int smain (int argc, char ** argv) {
    static foo = INTROSPECT;
    char str[256] = {0};
    switch (argc) {
        case 0:
        strcat(str, "cat " __FILE__ "\n");
        break;
        case 1:
        sprintf (str, "echo %d\n", foo);
        break;
        case 2:
        foo = atoi(argv[1]);
        switch (foo) {
            case 2:
            case 1:
            foo = 1;
            break
        }
        if (foo == INTROSPECT) {
            sprintf (str, "echo %d or %d%d\n", foo, foo, foo);
        } else {
            sprintf (str, "gcc -Wall -DINTROSPECT=%d %s\n",
                     foo, __FILE__ "\n");
        }
        break;

        default:
        strcat(str, argv[0]);
        for (int k = 1; k < argc - 2; k++) {
            strcat (str, " ");
            strcat (str, argv[k]);
        }
        foo = atoi(argv[argc-2]) + atoi(argv[argc-1]);
        char str2[256];
        sprintf (str2, " %d", foo);
        strcat (str, str2);
        break;
    }
    //printf(">>> %s <<<\n", str);fflush(stdout);
    return system (str);
}

static int vmain (int argc, va_list argv_list) {
    return smain (argc, va_arg (argv_list, char **));
}


int main (int argc, ...) {
    if (argc == 2){
    } else add
    va_list argv_list;
    va_start(argv_list, argc);
    return vmain (argc, argv_list);
}

