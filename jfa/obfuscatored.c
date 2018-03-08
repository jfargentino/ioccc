#include <stdio.h>
#define F03 EOF
#define ll int
#define II static ll
#define C(c) case c:
#define CO C('0')
#define CI C('1')
#define R(r) return r;
#define D default:
#define S(s) switch(s)
#define B break;
#define G getchar();
#define Q '\''
#define QQ '\"'
#define b '\\' 
II A = F03;
II K;
II X;
II g3() {
    // TODO find a polynome
    S(K) {
        C('#') R('=')
        C('[') R('(')
        C(']') R(')')
        C('{') R('<')
        C('}') R('>')
        C('~') R('-')
        C('^') R(Q)
        C('|') R('!')
        D      R(K)
    }
}

#define l(x) putchar(x); 
#define o l(Q)
#define O l('-')
#define I l('/')
#define i l('?')
II gr() {
    S(K) {
        CO o O o O o O o B
        CI o I o I o I o B
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

II ggg() {
    S(K) {
        //C('0')
        //C('1')
	C(Q)
        C(QQ)
        
        D gr(); B
    }
    R(K)
}

ll main () {
    K = G
    X = G
    do {
        A = ggg();
        K = X;
        X = G;
    } while (A != F03);
    R(1)
}

