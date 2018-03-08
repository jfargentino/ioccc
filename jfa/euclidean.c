
int gcd1 (int a, int b) {
    while (b > 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int gcd2 (int a, int b) {
    return (b > 0) ? gcd2(b, a % b) : a;
}

int gcd3 (int a, int b) {
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

