#include <stdio.h>
#include <unistd.h>

#define ff(file) fflush(file)
#define fmove(file, l, c) fprintf(file, "\e[%u;%uH", (l)+1, (c)+1); ff(file)
#define fsave(file) fprintf(file, "\e[s"); ff(file)
#define frestore(file) fprintf(file, "\e[s"); ff(file)
#define ferase(file) fprintf(file, "\e[2J"); ff(file)
#define ferasel(file) fprintf(file, "\e[K"); ff(file)

enum text_attr_t {
    TEXT_ATTR_OFF = 0,
    TEXT_ATTR_BOLD = 1,
    TEXT_ATTR_UNDER = 4,
    TEXT_ATTR_BLINK = 5,
    TEXT_ATTR_REVERSE = 7,
    TEXT_ATTR_CONCEALED = 8,
};

enum bg_color_t {
    BG_BLACK   = 40,
    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_YELLOW  = 43,
    BG_BLUE    = 44,
    BG_MAGENTA = 45,
    BG_CYAN    = 46,
    BG_WHITE   = 47,
};

enum fg_color_t {
    FG_BLACK   = 30,
    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_YELLOW  = 33,
    FG_BLUE    = 34,
    FG_MAGENTA = 35,
    FG_CYAN    = 36,
    FG_WHITE   = 37,
};

#define fmode(file, attr) fprintf(file, "\e[%um", attr)

void bg_map (enum bg_color_t const * bg, int h, int w) {
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            fmode(stdout, *bg); bg++;
            fprintf (stdout, " "); ff(stdout);
            usleep(5);
        }
        fprintf (stdout, "\n");
        usleep(500);
    }
    fmode(stdout, TEXT_ATTR_OFF);
}

struct pixel_t {
    char c;
    enum text_attr_t attr;
    enum fg_color_t fg;
    enum bg_color_t bg;
};

struct pixel_t const PIXEL_WHITE = { .c = ' ',
                                     .bg = BG_WHITE,
                                     .fg = FG_BLACK };

struct pixel_t const PIXEL_BLACK = { .c = ' ',
                                     .fg = FG_WHITE,
                                     .bg = BG_BLACK };

int fpixel (FILE * file, struct pixel_t const * pix) {
    return fprintf(file, "\e[%u;%um%c", pix->fg, pix->bg, pix->c);
}

void fmap2 (FILE* file, struct pixel_t const * p, int h, int w) {
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            fpixel(file, p);
            p++;
        }
    }
    fmode(file, 0);
}

void fmap (FILE* file, struct pixel_t const * p,
           int r, int c, int h, int w) {
    fmove(file, r, c);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            fpixel(file, p);
            p++;
        }
        fprintf (file, "\n");
    }
    fmode(file, 0);
}

#define fup(file)   fprintf(file, "\e[1A")
#define fdown(file) fprintf(file, "\e[1B")
#define fforw(file) fprintf(file, "\e[1C")
#define fback(file) fprintf(file, "\e[1D")
void fspiral (FILE* file, struct pixel_t const * p, int h, int w) {
    int sz = h * w;
    int count = 1;
    int right = 1;
    int down  = 1;
    int left  = 2;
    int up    = 2;
    int x = h/2 + 1;
    int y = w/2 + 1;
    fmove (file, x, y);
    while (sz) {
        fpixel (file, p++);
        //ff(file); usleep(1*1);
        if (right) {
            // nothing TODO, the cursor is at the right pos after fpixel
            right --;
            //y++;
        } else if (down) {
            down --;
            //x++;
            fback(file);
            fdown(file);
        } else if (left) {
            left --;
            //y--;
            fback(file);
            fback(file);
        } else if (up) {
            up --;
            //x --;
            fback(file);
            fup(file);
        }
        //fmove(file, x, y);
        if (!up) {
            count += 2;
            right = count;
            down  = count;
            left  = count + 1;
            up    = count + 1;
            usleep (1);
        }
        sz --;
    }
    fmode(file, 0);
}

void fspiralize (FILE* file, int step) {
    static int count = 1;
    static int right = 1;
    static int down  = 1;
    static int left  = 2;
    static int up    = 2;
    if (NULL == file) {
        count = 1;
        right = 1;
        down  = 1;
        left  = 2;
        up    = 2;
        return;
    }
    while (step > 0) {
        if (right) {
            fforw(file);
            right --;
        } else if (down) {
            down --;
            fdown(file);
        } else if (left) {
            left --;
            fback(file);
        } else if (up) {
            up --;
            fup(file);
        }
        if (!up) {
            count += 2;
            right = count;
            down  = count;
            left  = count + 1;
            up    = count + 1;
        }
    }
}

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t PRIME[1024*1024] = { 2 };
static uint64_t disp_sieve (uint64_t N, int col) {
    // keep only odd numbers
    struct pixel_t * sieve = malloc ((N/2)*sizeof(struct pixel_t));
    if (sieve == NULL) {
        return 0;
    }
    for (int k = 0; k < N/2; k++) {
        sieve[k] = PIXEL_WHITE;
    }
    uint64_t p = 3;
    size_t k = 1;
    while (p < N) {
        PRIME[k++] = p;
        for (uint64_t n = 3; n < N/p; n += 2) {
            size_t odd = (n*p)/2 - 1;
            if (n*p & 1) {
                if (sieve[odd].bg > BG_BLACK) {
                    sieve[odd].bg = (sieve[odd].bg == BG_WHITE)
                                                   ? BG_RED
                                                   : BG_BLACK;
                }
            }
        }
        p +=2;
        while ((p < N) && (sieve[p/2-1].bg < BG_WHITE)) {
            sieve[p/2-1].bg = BG_BLACK;
            sieve[p/2-1].fg = FG_WHITE;
            sieve[p/2-1].c  = ' ';
            p +=2;
        }
        fspiral(stdout, sieve, N/(2*col), col);usleep(50*1000);
    }
    fspiral(stdout, sieve, N/(2*col), col);usleep(50*1000);
    fmove(stdout, N/col+1, 1);
    free(sieve);
    return PRIME[k-1];
}

void plain (enum bg_color_t bg, int h, int w) {
    fmode(stdout, bg);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            fprintf (stdout, " "); ff(stdout);
            usleep(5);
        }
        fprintf (stdout, "\n");
        usleep(50);
    }
    fmode(stdout, TEXT_ATTR_OFF);
}

void area (enum bg_color_t bg, int r, int c, int h, int w) {
    fmode(stdout, bg);
    for (int x = 0; x < h; x++) {
        fmove(stdout, r+x, c);
        for (int y = 0; y < w; y++) {
            fprintf (stdout, " "); ff(stdout);
            usleep(5);
        }
        usleep(500);
    }
    fmode(stdout, TEXT_ATTR_OFF);
}

int main (void) {
    //int col = 199;
    //int row = 53;
    //int col = 57;
    //int col = 78; // font size 7
    int col = 135; // font size 4
    //int col = 203; // font size 2
    //int col = 411; // font size 1
    int row = col;
    //uint64_t N = 2*col*col;
    //uint64_t N = 20*1024;
    //int row = N/(2*col);
    uint64_t N = 2*row*col;
    ferase(stdout);
    //plain(BG_BLACK, row, col);
    fmove(stdout, 0, 0);
    disp_sieve (N, col);
/*
    fmove(stdout, 0, 0);
    ferase(stdout);
    plain(BG_BLUE, 40, 80);
    plain(BG_WHITE, 10, 80);
    area(BG_YELLOW, 35, 36, 10, 8);
*/
    sleep(1);
    return 0;
}

enum screen_t {
    SCREEN_40x25_MONO  = 0,
    SCREEN_40x25_COLOR = 1,
    SCREEN_80x25_MONO  = 2,
    SCREEN_80x25_COLOR = 3,
    SCREEN_320x200_4      = 4,
    SCREEN_320x200_MONO   = 5,
    SCREEN_640x200_MONO   = 6,
    SCREEN_LINE_WRAPPING  = 7,
    SCREEN_320x200_COLOR = 13,
    SCREEN_640x200_16    = 14,
    SCREEN_640x350_MONO  = 15,
    SCREEN_640x350_16    = 16,
    SCREEN_640x480_MONO  = 17,
    SCREEN_640x480_16    = 18,
    SCREEN_320x200_256   = 19,
};

#define fscreen(file, mode) fprintf(file, "\e[=%uh", mode); ff(file)
#define freset(file, mode) fprintf(file, "\e[=%ul", mode); ff(file)

