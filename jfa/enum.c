#include <stdio.h>
#include <stdint.h>

#if 1
enum an_enum {
    AN_ENUM_1st = 255,
    AN_ENUM_2nd,
    AN_ENUM_3rd,
}__attribute__((packed));

enum another_enum {
    ANOTHER_ENUM_1st = 255,
    ANOTHER_ENUM_2nd,
    ANOTHER_ENUM_3rd,
};

int main (void) {
    enum an_enum a;
    enum another_enum b;
    printf ("%zu, %zu\n", sizeof(enum an_enum), sizeof(enum another_enum));
    a = AN_ENUM_1st;
    b = ANOTHER_ENUM_2nd;
    printf ("%zu, %zu\n", sizeof(a), sizeof(b));
    b = a;
    a = ANOTHER_ENUM_2nd;
    printf ("%zu, %zu\n", sizeof(a), sizeof(b));
    return 0;
}
#else
typedef enum {
    AN_ENUM_1st = (uint8_t)0x01,
    AN_ENUM_2nd = (uint8_t)0x02,
    AN_ENUM_3rd = (uint8_t)0x03,
} an_enum;

typedef enum {
    ANOTHER_ENUM_1st,
    ANOTHER_ENUM_2nd,
    ANOTHER_ENUM_3rd,
} another_enum;

int main (void) {
    an_enum a;
    another_enum b;
    printf ("%zu, %zu\n", sizeof(an_enum), sizeof(another_enum));
    a = AN_ENUM_1st;
    b = ANOTHER_ENUM_2nd;
    printf ("%zu, %zu\n", sizeof(a), sizeof(b));
    b = a;
    a = ANOTHER_ENUM_2nd;
    printf ("%zu, %zu\n", sizeof(a), sizeof(b));
    return 0;
}
#endif

////////////////////////////////////////////////////////////////////////////////
//-Werror
//-fstrict-aliasing
//-Wstrict-aliasing=2
//-fsyntax-only
//-pedantic
//-pedantic-errors clang-3.8: #include_next ... pourtant pas de warn !
//-std=c99
//-w
//-Waggregate-return
//-Wall
//-Wextra
//-Wbad-function-cast
//-Wcast-align
//-Wcast-qual
//-Wchar-subscripts
//-Wcomment
//-Wconversion
//-Wdisabled-optimization
//-Wdiv-by-zero
//-Wenum-conversion gcc-5: error: unrecognized command line option ‘-Wenum-conversion’
//-Werror-implicit-function-declaration
//-Wfloat-equal
//-Wformat=2
//-Wformat-security
//-Wformat
//-Wmissing-format-attribute
//-Wformat-nonliteral
//-Wimplicit
//-Wimplicit-function-declaration
//-Wimplicit-int
//-Wimport
//-Winline
//-Wlarger-than-longueur gcc-5: error: argument to ‘-Wlarger-than=’ should be a non-negative integer
//-Wlogical-op
//-Wlong-long
//-Wmain
//-Wmissing-braces
//-Wmissing-declarations
//-Wmissing-noreturn
//-Wmissing-prototypes
//-Wmultichar
//-Wnested-externs
//-Wno-format-extra-args
//-Wno-format-y2k
//-Wno-import
//-Wnonnull
//-Wno-old-style-declaration
//-Wpacked
//-Wpadded
//-Wparentheses
//-Wpointer-arith
//-Wredundant-decls
//-Wreturn-type
//-Wsequence-point
//-Wshadow
//-Wshift-count-negative
//-Wshift-count-overflow
//-Wsign-compare
//-Wstrict-prototypes
//-Wswitch
//-Wswitch-bool
//-Wsystem-headers
//-Wtraditional
//-Wtrigraphs
//-Wundef
//-Wuninitialized
//-Wunknown-pragmas
//-Wunreachable-code
//-Wunused
//-Wunused-function
//-Wunused-label
//-Wunused-parameter
//-Wunused-value
//-Wunused-variable
//-Wwrite-strings
//
//
//
