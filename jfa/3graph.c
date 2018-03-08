#include <stdio.h>
#define F03 EOF
#define ll int
#define II static ll
#define C(c) case c:
#define R(r) return r;
#define D default:
#define S(s) switch(s)
#define B break;
#define G getchar();
#define b '\\' 
II K;
II g3() {
    // TODO find a polynome
    S(K) {
        C('#') R('=')
        C('[') R('(')
        C(']') R(')')
        C('{') R('<')
        C('}') R('>')
        C('~') R('-')
        C('^') R('\'')
        C('|') R('!')
        D      R(K)
    }
}

#define l(x) putchar(x); 
#define i l('?')
II gr() {
    S(K) {
        C('#')
        C('[')
        C(']')
        C('{')
        C('}')
        C('~')
        C('^')
        C('|')
        i i
        // TODO once g3 is a polynome
        // K = g3(); then l(K);
        D l(g3()) B
    }
    R(K)
}

ll main () {
    K = G
    do {
        gr();
        K = G;
    } while (K != F03);
    R(1)
}

