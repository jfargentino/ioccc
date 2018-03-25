#ifndef XORFILE_H
#define XORFILE_H

#include "xorstream.h"
#include <stdio.h>

void xorbin32 (FILE * file, uint32_t round,
               enum xorshift_t method, uint32_t * seed32);

void xorhex32 (FILE * file, uint32_t round,
               enum xorshift_t method, uint32_t * seed32);

void xorbin64 (FILE * file, uint32_t round,
               enum xorshift_t method, uint64_t * seed64);

void xorhex64 (FILE * file, uint32_t round,
               enum xorshift_t method, uint64_t * seed64);

void xorbin (FILE * file, uint32_t round,
             enum xorshift_t method, uint32_t * seed32);

void xorhex (FILE * file, uint32_t round,
             enum xorshift_t method, uint32_t * seed32);

#endif

