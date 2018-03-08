#include <stdio.h>

/*
    
??=define ___def1ne int
??=define ___o0O(_,...) main(___def1ne _, ??=??=__VA_ARGS__)
___def1ne ___o0O(_,...) ??<
    int a??('/'/'/'??) = ??< '/'/'/' ??>;
    int b = '/'/'/';
    int c = ??-b;
    b = ??('-'-'-'??)a ??' c;
    c = ??('-'-'-'??)a ??! b;
    return c;
??>

*/

int main(void) {
    char const * A = "ABCDFEGH"; 
    char const * B = "%sA%sB%sC%sD%sF%sE%sG%sH%s"; 
    char const * C = "%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s"; 
    for (int k = 0; k < 8; k++) {
        //printf ("%d ", k["ABCDFEGH"]);
        //printf ("%02x ", k[A]);
        printf (B,
                k == 0 ? "[" : "",
                k == 0 ? "]" : k == 1 ? "[" : "",
                k == 1 ? "]" : k == 2 ? "[" : "",
                k == 2 ? "]" : k == 3 ? "[" : "",
                k == 3 ? "]" : k == 4 ? "[" : "",
                k == 4 ? "]" : k == 5 ? "[" : "",
                k == 5 ? "]" : k == 6 ? "[" : "",
                k == 6 ? "]" : k == 7 ? "[" : "",
                               k == 7 ? "]\n" : "\n");
        printf (C,
                k == 0 ? "[" : "", 0[A],
                k == 0 ? "]" : k == 1 ? "[" : "", 1[A],
                k == 1 ? "]" : k == 2 ? "[" : "", 2[A],
                k == 2 ? "]" : k == 3 ? "[" : "", 3[A],
                k == 3 ? "]" : k == 4 ? "[" : "", 4[A],
                k == 4 ? "]" : k == 5 ? "[" : "", 5[A],
                k == 5 ? "]" : k == 6 ? "[" : "", 6[A],
                k == 6 ? "]" : k == 7 ? "[" : "", 7[A],
                k == 7 ? "]\n" : "\n");
    }

    int k = 0;
    switchk:switch(k){
        default:
        printf ("%d ", k++);
        int x = k, goto switchk;
        case 6:
        putchar('\n');
    }
    return 0;
}

