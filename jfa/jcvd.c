#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * jcvd = "jcvd";
int p   = 1;
int one = 0;
    #define JCVD_SAYS printf("%s says ", jcvd);
    #define argoi(arg) atoi(argv[(arg)])
    #define arg0i argoi(0)
    #define argo1 argoi(1)
    #define ARG0I if(p)printf("%d",arg0i);
    #define JCVD  ( (strcmp (argv[0],   jcvd) == 0) \
                 || (strcmp (argv[0]+2, jcvd) == 0) )
    #define ONEORELEVEN main(0,0)
    #define ONEISELEVEN main(1,&jcvd)
    #define ONEORONEONE printf(" ... %s %d %c\n",       \
                               one == 11 ? "or" : "is", \
                               ONEORELEVEN,             \
                               one == 11 ? '?' : '!'    )
    #define ONEISEONEONE main(argc-1, argv+1)
    #define O "%*.f"
    #define o 0.7
    #define NE one, o
    #define ONE printf(O,NE);
    #define ONEONE NE + o
    #define ELEVEN printf(O, ONEONE)
    #define PLUS  if(p)printf(" + ");
    #define EQUAL if(p)printf(" = ");
    #define ADD one += arg0i;
    #define ONEIS0 (arg0i == 1)
    #define ON3IS0 (argo1 == 1)
    #define ONEIS1 (one   == 1)
    #define pONE p = 1
    #define p0NE p = 0
    #define ONEONEISELEVEN one=11;
int main (int argc, char ** argv) {
    if (argc <= 1) {
        if (argc > 0) {
            if (JCVD) {
                JCVD_SAYS ONE PLUS ONE EQUAL ELEVEN;
                ONEONEISELEVEN
                ONEORONEONE;
            } else if (ONEIS0 && ONEIS1) return ONEISELEVEN; else {
                ADD
                ARG0I
                EQUAL
                printf ("%d\n", one);
            }
        }
        return one;
    }
    if (JCVD) {
        argc --;
        argv ++;
        if ((argc != 2)||!ONEIS0||!ON3IS0) JCVD_SAYS
        else p0NE;
    }
    ADD
    ARG0I
    if (argc == 1) {
        if (ONEIS0) ONEONEISELEVEN
        ONEORONEONE;
        return ONEORELEVEN;
    }
    PLUS
    pONE;
    return ONEISEONEONE; 
}

