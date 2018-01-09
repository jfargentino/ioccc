#!/bin/bash

if [[ $# -eq 0 ]]; then
    N=63
    n=0
    while [[ $n < $N ]]; do
        if [[ $n -lt 10 ]]; then
            nn='0'$n
        else
            nn=$n
        fi
        cc self-"$nn".c -o self"$nn" && ./self"$nn" > self-"$nn".d
        if [[ -f self-"$nn".d ]]; then
            diff self-"$nn".c self-"$nn".d > self-"$nn".e
        fi
        n=$(( n + 1 ))
    done
else
    for n in "$@"; do
        if [[ $n -lt 10 ]]; then
            nn='0'$n
        else
            nn=$n
        fi
        cc self-"$nn".c -o self"$nn" && ./self"$nn" > self-"$nn".d
        if [[ -f self-"$nn".d ]]; then
            diff self-"$nn".c self-"$nn".d > self-"$nn".e
        fi
    done
fi
