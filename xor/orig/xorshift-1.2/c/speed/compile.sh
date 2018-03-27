#!/bin/bash

gcc -Wall -Wno-unused-variable -O3 -std=c99 jrand-speed.c -o jrand-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 loop-speed.c -o loop-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 lehmer128-speed.c -o lehmer128-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 pcg64-speed.c -o pcg64-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 mt19937-speed.c -o mt19937-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 ran-speed.c -o ran-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 splitmix-speed.c -o splitmix-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 well1024a-speed.c -o well1024a-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 well19937a-speed.c -o well19937a-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xorgens4096-speed.c -o xorgens4096-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 -DA=31 -DB=11 -DC=30 xorshift1024-speed.c -o xorshift1024-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 -DA=31 -DB=11 -DC=30 xorshift1024star32-speed.c -o xorshift1024star32-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 -DA=23 -DB=17 -DC=26 xorshift128plus-speed.c -o xorshift128plus-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xorshift4096-speed.c -o xorshift4096-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xorshift4096star32-speed.c -o xorshift4096star32-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xorshift64-speed.c -o xorshift64-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xorshift64star32-speed.c -o xorshift64star32-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 -DA=55 -DB=14 -DC=36 xoroshiro128plus-speed.c -o xoroshiro128plus-speed
gcc -Wall -Wno-unused-variable -O3 -std=c99 xsadd-speed.c -o xsadd-speed
gcc -Wall -Wno-unused-variable -Wno-strict-aliasing -O3 -std=c99 -DHAVE_SSE2 -DSFMT_MEXP=19937 sfmt-speed.c -o sfmt19937-speed
