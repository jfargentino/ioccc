#include <stdio.h>

unsigned int SPIRAL[512*1024][2];
static void spiral (unsigned int h, unsigned int w) {
    unsigned int count = 1;
    unsigned int right = count;
    unsigned int down  = count;
    unsigned int left  = count + 1;
    unsigned int up    = count + 1;
    unsigned int k     = 0;  
    unsigned int row   = h/2+1;  
    unsigned int col   = w/2+1;  
    0[k[SPIRAL]] = row;
    1[k[SPIRAL]] = col;
    while (k < h*w) { // test against h and w ?
        if (right) {
            col ++;
            right --;
        } else if (down) {
            row ++;
            down --;
        } else if (left) {
            col --;
            left --;
        } else if (up) {
            row --;
            up --;
        }
        if (!up) {
            count += 2;
            right = count;
            down  = count;
            left  = count + 1;
            up    = count + 1;
        }
        k ++;
        0[k[SPIRAL]] = row;
        1[k[SPIRAL]] = col;
    }
}

#define ff(file) fflush(file)
#define fmove(file, l, c) fprintf(file, "\e[%u;%uH", (l)+1, (c)+1);
#define fpixel(file, bg) fprintf(file, "\e[%um ", bg)

enum bg_color_t {
    BG_BLACK   = 40,
    BG_RED     = 41,
    BG_WHITE   = 47,
};

unsigned int PRIME[1024*1024] = { 2 };
enum bg_color_t SIEVE[1024*1024];

static unsigned int fsieve (FILE* file, unsigned int N, unsigned int col) {
    if (N/2 > 1024*1024) {
        return 0;
    }
    spiral(N/(2*col) + 1, col);
    for (unsigned int k = 0; k < N/2; k++) {
        SIEVE[k] = BG_WHITE;
        fmove(file, SPIRAL[k][0], SPIRAL[k][1]);
        fpixel(file, SIEVE[k]);
    }
    unsigned int p = 3;
    unsigned int k = 1;
    while (p < N/3) {
        unsigned int odd = p/2 - 1;
        PRIME[k++] = p;
        SIEVE[p/2-1]--;
        fmove(file, SPIRAL[odd][0], SPIRAL[odd][1]);
        fpixel(file, SIEVE[odd]);
        ff(file);
        for (unsigned int n = 3; n < N/p; n += 2) {
            if (n*p & 1) {
                unsigned int odd2 = (n*p)/2 - 1;
                SIEVE[odd2] = (SIEVE[odd2] == BG_WHITE) ? BG_RED : BG_BLACK;
                fmove(file, SPIRAL[odd2][0], SPIRAL[odd2][1]);
                fpixel(file, SIEVE[odd2]);
            }
        }
        p +=2;
        odd = p/2 - 1;//odd++;
        while ((p < N/3) && (SIEVE[odd] < BG_WHITE)) {
            SIEVE[odd] = BG_BLACK;
            fmove(file, SPIRAL[odd][0], SPIRAL[odd][1]);
            fpixel(file, SIEVE[odd]);
            p +=2;
            odd = p/2 - 1;//odd++;
        }
        odd = PRIME[k-1]/2-1;
        SIEVE[odd]++;
        fmove(file, SPIRAL[odd][0], SPIRAL[odd][1]);
        fpixel(file, SIEVE[odd]);
        ff(file);
    }
    fmove(file, N/col+1, 1);
    fprintf (file, "\e[0m\n");
    return k;
}

int main (void) {
    //unsigned int col = 57;
    unsigned int col = 78; // font size 7
    //unsigned int col = 135; // font size 4
    //unsigned int col = 203; // font size 2
    //unsigned int col = 411; // font size 1
    unsigned int row = col;
    unsigned int N = 2*row*col;
    fprintf(stdout, "\e[2J");
    unsigned int k = fsieve (stdout, N, col);
    //printf ("\n%u primes under %u, highest is %u\n", k, N, PRIME[k - 1]);
    /*
    for (unsigned int n = 0; n < k; n++) {
        printf ("\tPRIME[%u] = %u\n", n, PRIME[n]);
    }
    */
    return 0;
}

