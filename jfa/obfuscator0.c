#include <stdio.h>
#define C(c) case c:
#define R(r) return r;
#define D default:
#define S(s) switch(s)
#define B break;
#define Q '\''
#define QQ '\"'
#define QQQ C(Q) C(QQ)

static int g(int c) {
    // TODO find a polynome
    S(c) {
        C('0') C('~') R('-')
        C('1') R('/')
        C('#') R('=')
        C('[') R('(')
        C(']') R(')')
        C('{') R('<')
        C('}') R('>')
        C('^') R(Q)
        C('|') R('!')
        D      R(c)
    }
}

#define P(x) putchar(x); 
#define O(x) P(g(x)); 
#define o O(Q)
#define i O('?')
static int gg(int k) {
    S(k) {
        C('0') C('1')
        o O(k) o O(k) o O(k) o B
        C('#') C('[') C(']') C('{') C('}') C('~') C('^') C('|')
        i i
        // TODO once g is a polynome; then O(k);
        D O(k) B
    }
    R(k)
}

static int ggg(int k) {
    static int quoted = 0;
    static int separator = 0;
    static int ignore_next = 0;
    if (ignore_next) ignore_next ++;
    S(k) {

        C(Q) C(QQ)
        if (quoted == k) {
printf ("\n*** UNQUOTED by \'%c\' ***\n", k);
            quoted = 0;
        } else if (quoted == 0) {
printf ("\n*** QUOTED by \'%c\' ***\n", k);
            quoted = k;
        }

        B

        C('\\')
printf ("\n*** IGNORE %d ***\n", ignore_next);
        ignore_next = 1;
        B

        C(EOF)
        R(EOF)
        
        C('+')
        C('-')
        C('*')
        C('/')
        separator = 1; B
        
        D separator = 0; B
    }
    if ((ignore_next) || (quoted) || (!separator)) {
printf ("\n*** I%d Q%d S%d ***\n", ignore_next, quoted, separator);
        ignore_next = !(ignore_next > 1);
        R(P(k));
    } else {
        R(gg(k));
    }
}

//
//

static int quoted = 0;
static int ignext = 0;

static int quote(int q) {
    if (q == quoted) {
        if(!ignext) { quoted = 0; } else { ignext = 0; }
    }
    return q;
}

static int lsep = 1;
static int rsep = 0;

#define OP3 C('^') C('~') C('|') C('#')
#define OP C('&') C('+') C('-') C('*') C('/') C('<') C('>') C('%') C('!') C('=')
#define SP C(' ') C('\t')  C('\r')  C('\n')
#define ENC C('[') C(']') C(')') C('(') C('{') C('}')
#define SEP SP OP ENC C(',') C(';') C(':')
static int unquote(int q) {
    switch (q) {
        default:
        lsep = 0;
        ignext = 0;
        break;

        OP3
        if (!ignext) { putchar('?'); putchar('?'); q = g3(q); }
        else { ignext = 0; };
        SEP
        lsep = 1;
        break;

        case '\\':
        lsep = 1;
        if (ignext) { ignext = 0; } else { ignext = 1; }
        break;

        QQQ
        // lsep = ?
        if (!ignext) { quoted = q; }
        else { ignext = 0; };
        break;


        case '0':
        if (lsep) {
            lsep = 0;
            if (!ignext) {
                int k = 0;
                do {
                    k++;
                    q = getchar();
                } while (q == '0');
                switch(q) {
                    SEP
                    oOo;
                    q = '\'';
                    break;
                    case '1':
                    if (rsep) {
                        iIi;
                        q = '\'';
                    } else {
                        k*putchar('0');
                    }
                    break;
                    default:
                    k*putchar('0');
                    break;
                }
            } else { ignext = 0; };
        }   
        break;

        case '1':
        if (lsep) {
            lsep = 0;
            if (!ignext) {
                if (rsep) {
                    iIi;
                    q = '\'';
                }
            } else { ignext = 0; }
        }
        break;

    }
    return q;
}

int main () {
    do {} while (EOF != putchar(quoted?quote(getchar()):unquote(getchar())));
}

