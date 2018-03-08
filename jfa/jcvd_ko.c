#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char ** argv) {
    static char * jcvd = "jcvd";
    static int p   = 1;
    static int one = 0;
    #define JCVD_SAYS printf("%s says ", jcvd)
    #define argoi(arg) atoi(argv[(arg)])
    #define arg0i argoi(0)
    #define argo1 argoi(1)
    #define ARG0I if(p){ printf ("%d", arg0i); }
    #define check(str)  ( (strcmp (argv[0],   str) == 0) \
                       || (strcmp (argv[0]+2, str) == 0) )
    #define ONEORONEONE(one) printf(" ... %s %d %c\n",       \
                                    one == 11 ? "or" : "is", \
                                    main(0, NULL),           \
                                    one == 11 ? '?' : '!'    )
    #define ONE "%*.f"
    #define ON3 one, 0.7
    #define ONEONE ON3 + 0.7
    #define PLUS " + "
    #define EQUAL  " = " 
    switch (argc) {
        case 0:
        return one;

        case 1:
        if (check(jcvd)) {
            JCVD_SAYS;
            printf (ONE, ON3);
            if (p) {printf(PLUS);}
            printf (ONE, ON3);
            if (p) {printf(EQUAL);}
            printf (ONE, ONEONE);
            one = 11;
            ONEORONEONE(one);
        } else if ((arg0i == 1) && (one == 1)) {
            return main(1, &jcvd);
        } else {
            one += arg0i;
            printf ("%d", arg0i);
            if (p) {printf(EQUAL);}
            printf ("%d\n", one);
        }
        return one;
        
        default:
        if (check(jcvd)) {
            argc --;
            argv ++;
            if ((argc != 2) || (arg0i != 1) || (argo1 != 1)) {
                JCVD_SAYS;
            } else {
                p = 0;
            }
        }
        one += arg0i;
        ARG0I;
        if (argc == 1) {
            if (arg0i == 1) {
                one = 11;
            }
            ONEORONEONE(one);
            return main (0, NULL);
        }
        if (p) {printf(PLUS);}
        return main(argc-1, argv+1);
    }
    return -11;
}

