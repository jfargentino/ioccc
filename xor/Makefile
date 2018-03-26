all: check

SRC=main.c uuid4.c seed.c xorjump.c xorshift.c xorfile.c xorstream.c
OBJ=$(patsubst %.c, %.o, $(SRC))

scheck: $(SRC)
	@cppcheck --enable=all --inconclusive --std=posix $^

uuid4: $(OBJ)

DIEHARDER=xorshift32 xorshift128 xorwow splitmix64 xorshift64star \
		  xorshift1024star xorshift128plus xoroshiro128plus

$(DIEHARDER): $(SRC)
	./uuid4 -b -x $@ 32768 | dieharder -a > $@.txt

dieharder: $(DIEHARDER)

REF=orig/uuid4/example/example
REF_SRC=orig/uuid4/src/uuid4.c orig/uuid4/example/example.c

$(REF): uuid4.patch $(REF_SRC)
	@patch -p1 -N --dry-run -d orig/uuid4 < uuid4.patch \
		&& patch -p1 -N -d orig/uuid4 < uuid4.patch
	@cd orig/uuid4/example/ && ./build.sh && cd ../../..

ref: $(REF)

check: uuid4 ref check.sh
	@./check.sh

clean:
	@rm -v uuid4 $(REF) $(OBJ)

distclean: clean
	@cd orig/uuid4/ && git reset --hard && cd ../..
	@rm .SEED .UUID*

.PHONY = distclean clean check scheck

#CC=clang-5.0
CC=gcc

LDFLAGS+=-lrt

# Misc #########################################################################
#CPPFLAGS+=-std=c99
CPPFLAGS+=-fstrict-aliasing -Wstrict-aliasing=2
CPPFLAGS+=-Wall -Wextra
CPPFLAGS+=-Wbad-function-cast -Wcast-align -Wcast-qual
CPPFLAGS+=-Winline
CPPFLAGS+=-Wpointer-arith
CPPFLAGS+=-Wshadow
CPPFLAGS+=-Wstrict-prototypes
CPPFLAGS+=-Wmissing-prototypes 
CPPFLAGS+=-Wchar-subscripts
CPPFLAGS+=-Wwrite-strings
CPPFLAGS+=-Wformat -Wmissing-format-attribute -Wformat-nonliteral
CPPFLAGS+=-Wundef
CPPFLAGS+=-Wfloat-equal
CPPFLAGS+=-Wpadded
CPPFLAGS+=-Wunreachable-code
CPPFLAGS+=-Wredundant-decls
CPPFLAGS+=-Wnested-externs
CPPFLAGS+=-Wno-old-style-declaration
CPPFLAGS+=-Wlogical-op
CPPFLAGS+=-Wnonnull
# Flags for GCC5 ###############################################################
CPPFLAGS+=-Wshift-count-negative
CPPFLAGS+=-Wshift-count-overflow
CPPFLAGS+=-Wswitch-bool

# Flags for GCC6 ###############################################################
#CPPFLAGS+=-Wduplicated-cond
#CPPFLAGS+=-Wtautological-compare
#CPPFLAGS+=-Wshift-negative-value
#CPPFLAGS+=-Wshift-overflow=2
#CPPFLAGS+=-Wnull-dereference
#CPPFLAGS+=-Woverride-init-side-effects
#CPPFLAGS+=-Wunused-const-variable
#CPPFLAGS+=-Wframe-address
# TODO #########################################################################
CPPFLAGS+=-pedantic
CPPFLAGS+=-pedantic-errors
CPPFLAGS+=-w 
CPPFLAGS+=-Waggregate-return
CPPFLAGS+=-Wcomment
CPPFLAGS+=-Wconversion
CPPFLAGS+=-Wdisabled-optimization
CPPFLAGS+=-Wdiv-by-zero
#CPPFLAGS+=-Werror
CPPFLAGS+=-Wfloat-equal
CPPFLAGS+=-Wformat=2
CPPFLAGS+=-Wformat-security
CPPFLAGS+=-Wimplicit
CPPFLAGS+=-Wimplicit-int
CPPFLAGS+=-Wimplicit-function-declaration
CPPFLAGS+=-Werror-implicit-function-declaration
CPPFLAGS+=-Wimport
#CPPFLAGS+=-Wlarger-than-longueur
CPPFLAGS+=-Wlong-long
CPPFLAGS+=-Wmain
CPPFLAGS+=-Wmissing-braces
CPPFLAGS+=-Wmissing-declarations
CPPFLAGS+=-Wmissing-noreturn
CPPFLAGS+=-Wmultichar
CPPFLAGS+=-Wno-format-extra-args
CPPFLAGS+=-Wno-format-y2k
CPPFLAGS+=-Wno-import
CPPFLAGS+=-Wpacked
CPPFLAGS+=-Wpadded
CPPFLAGS+=-Wparentheses
CPPFLAGS+=-Wreturn-type
CPPFLAGS+=-Wsequence-point
CPPFLAGS+=-Wsign-compare
CPPFLAGS+=-Wswitch
CPPFLAGS+=-Wsystem-headers
CPPFLAGS+=-Wtrigraphs
CPPFLAGS+=-Wundef
CPPFLAGS+=-Wuninitialized
CPPFLAGS+=-Wunknown-pragmas
CPPFLAGS+=-Wunused
CPPFLAGS+=-Wunused-function
CPPFLAGS+=-Wunused-label
CPPFLAGS+=-Wunused-parameter
CPPFLAGS+=-Wunused-value
CPPFLAGS+=-Wunused-variable
CPPFLAGS+=-Wtraditional
#CPPFLAGS+=-Wenum-conversion
#CPPFLAGS+=-fsyntax-only
