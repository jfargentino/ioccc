#!/bin/bash

_do_one () {
    if [[ $1 -lt 10 ]]; then
        k='0'$1
    else
        k=$1
    fi
    cc self-"$k".c -o self-"$k" 2> self-"$k".d
    if [[ -e self-"$k" ]]; then
        ./self-"$k" | sed '/^$/d' > self-"$k".d
        if [[ -f self-"$k".d ]]; then
            diff -B -Z --strip-trailing-cr self-"$k".c self-"$k".d > self-"$k".e
            sz=$(wc -c < self-"$k".e)
            if [[ $sz -eq 0 ]]; then
                echo -e "\e[42m###\e[0m\e[32mself-$k\e[0m"
                rm self-"$k".e
            else
                echo -e "\e[43m???\e[0m\e[33mself-$k\e[0m"
                cat self-"$k".e
                echo -e "\e[43m???\e[0m"
            fi
        else
            echo -e "\e[41m!!! ERROR executing self-$k !!!\e[0m"
        fi
    else
        echo -e "\e[41m!!! ERROR building self-$k !!!\e[0m"
    fi
    echo
}

if [[ $# -eq 0 ]]; then
    N=63
    n=0
    while [[ $n -le $N ]]; do
        _do_one "$n"
        n=$(( n + 1 ))
    done
else
    for n in "$@"; do
        _do_one "$n"
    done
fi
