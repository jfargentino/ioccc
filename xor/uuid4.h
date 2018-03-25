/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef UUID4_H
#define UUID4_H

#include "seed.h"

#define UUID4_VERSION "0.1.1"
#define UUID4_LEN (32+5)

#define  uuid4_init_seed(seed) seed128((uint32_t*)(seed))
uint64_t uuid4_generate(uint64_t seed[2], char dst[UUID4_LEN]);
uint64_t uuid4_generate_xoro(uint64_t seed[2], char dst[UUID4_LEN]);

#endif

