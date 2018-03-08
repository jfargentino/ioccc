#include <stdlib.h>
#include <stdio.h>

int recursive_factorial (int n) {
    switch (n) {
        case 0:
        case 1:
        return 1;
        case 2:
        return 2;
        case 3:
        return 6;
        case 4:
        return 24;
        case 5:
        return 120;
        case 6:
        return 720;
        case 7:
        return 5040;
        case 8:
        return 40320;
        case 9:
        return 362880;
        case 10:
        return 3628800;
        case 11:
        return 39916800;
        case 12:
        return 479001600;
/*
        case 13:
        return 6227020800;
		case 14:
        87178291200;
		case 15:
        1307674368000;
		case 16:
        20922789888000;
		case 17:
        355687428096000;
*/
        default:
        return n * recursive_factorial (n - 1);
    }
    return 1;
}

int main (int argc, char ** argv) {
    for (int k = 1; k < argc; k++) {
        int x = atoi (argv[k]);
        int f = recursive_factorial (x);
        printf ("%10d! = %d\n", x, f);
    }
    return 0;
}

