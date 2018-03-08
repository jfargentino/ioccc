#include <stdio.h>

#define ff(file) fflush(file)
#define fup(file)   fprintf(file, "\e[1A")
#define fdown(file) fprintf(file, "\e[1B")
#define fforw(file) fprintf(file, "\e[1C")
#define fback(file) fprintf(file, "\e[1D")
#define fmove(file, l, c) fprintf(file, "\e[%u;%uH", (l)+1, (c)+1);
#define ferase(file) fprintf(file, "\e[2J"); ff(file)
#define fpixel(file, bg) fprintf(file, "\e[%um ", bg)
#define foff(file) fpixel(file, 0)

enum bg_color_t {
    BG_BLACK   = 40,
    BG_RED     = 41,
    BG_WHITE   = 47,
};

// TODO construct the spiral as a vector then we can use it to address the
//      spiral inside the sieve construction by using fmove:
//      SPIRAL[0]=[H/2+1][W/2+1]
//      SPIRAL[1]=[H/2+2][W/2+1]
//      SPIRAL[2]=[H/2+2][W/2+0] ...
//
void fspiral (FILE* file, enum bg_color_t const * p,
              unsigned int h, unsigned int w) {
    unsigned int sz = h * w;
    unsigned int count = 1;
    unsigned int right = count;
    unsigned int down  = count;
    unsigned int left  = count + 1;
    unsigned int up    = count + 1;
    while (sz) {
        fpixel(file, *p);
        ff(file);
        p++;
        if (right) {
            // nothing TODO, the cursor is at the right pos after fpixel
            right --;
        } else if (down) {
            down --;
            fback(file);
            fdown(file);
        } else if (left) {
            left --;
            fback(file);
            fback(file);
        } else if (up) {
            up --;
            fback(file);
            fup(file);
        }
        if (!up) {
            count += 2;
            right = count;
            down  = count;
            left  = count + 1;
            up    = count + 1;
        }
        sz --;
    }
    foff(file);
}


unsigned int PRIME[1024*1024] = { 2 };
enum bg_color_t SIEVE[1024*1024];

static unsigned int fsieve (FILE* file, unsigned int N, unsigned int col) {
    if (N/2 > 1024*1024) {
        return 0;
    }
    for (unsigned int k = 0; k < N/2; k++) {
        SIEVE[k] = BG_WHITE;
    }
    unsigned int p = 3;
    unsigned int k = 1;
    while (p < N/3) {
        PRIME[k++] = p;
printf ("\e[0m\rPRIME[%u] = %u\n\n", k-1, PRIME[k-1]);
        SIEVE[p/2-1]--;
        for (unsigned int n = 3; n < N/p; n += 2) {
            if (n*p & 1) {
                unsigned int odd = (n*p)/2 - 1;
                SIEVE[odd] = (SIEVE[odd] == BG_WHITE) ? BG_RED : BG_BLACK;
            }
        }
        p +=2;
        while ((p < N/3) && (SIEVE[p/2-1] < BG_WHITE)) {
            SIEVE[p/2-1] = BG_BLACK;
            p +=2;
        }
        //ferase(file);
        fmove (file, N/(4*col) + 1, col/2 + 20);
        fspiral(file, SIEVE, N/(2*col), col);
        SIEVE[PRIME[k-1]/2-1]++;
    }
    fmove (file, N/(4*col) + 1, col/2 + 20);
    fspiral(file, SIEVE, N/(2*col), col);
    fmove(file, N/col+1, 1);
    return k;
}

int main (void) {
    //unsigned int col = 57;
    //unsigned int col = 78; // font size 7
    unsigned int col = 135; // font size 4
    //unsigned int col = 203; // font size 2
    //unsigned int col = 411; // font size 1
    unsigned int row = col;
    unsigned int N = 2*row*col;
    ferase(stdout);
    fmove(stdout, 0, 0);
    unsigned int k = fsieve (stdout, N, col);
    printf ("%u primes under %u\n", k, N);
    /*
    for (unsigned int n = 0; n < k; n++) {
        printf ("\tPRIME[%u] = %u\n", n, PRIME[n]);
    }
    */
    return 0;
}

