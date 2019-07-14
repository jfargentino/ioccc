#include "gput.h"

int main(void) {
    int x = -12345;
    gput( "int -12345: ", stdout);
    gput(x, stdout);
    gput("\n", stdout);
 
    double y = -12345.54321;
    gput("double -12345.54321: ", stdout);
    gput(y, stdout);
    gput("\n", stdout);

    char a[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd',
        ' ', 'b', 'i', 's', '\0'};
    gput("char array :", stdout);
    gput(a, stdout);
    gput("\n", stdout);

    char const * s = "Hello, world!";
    gput("string: ", stdout);
    gput(s, stdout);
    gput("\n", stdout);

    void const * p = &y;
    gput("pointer :", stdout);
    gput(p, stdout);
    gput("\n", stdout);

    p = s;
    gput("pointer (bis):", stdout);
    gput(p, stdout);
    gput("\n", stdout);

    p = a;
    gput("pointer (ter):", stdout);
    gput(p, stdout);
    gput("\n", stdout);

    return 0;
}

