#!/bin/bash

_do_one () {
    if [[ $1 -lt 10 ]]; then
        k='0'$1
    else
        k=$1
    fi
    cc -trigraphs quine-"$k".c -o quine-"$k" 2> quine-"$k".d
    if [[ -e quine-"$k" ]]; then
        ./quine-"$k" | sed '/^$/d' > quine-"$k".d
        if [[ -f quine-"$k".d ]]; then
            diff -B -Z --strip-trailing-cr quine-"$k".c quine-"$k".d > quine-"$k".e
            sz=$(wc -c < quine-"$k".e)
            if [[ $sz -eq 0 ]]; then
                echo -e "\e[42m###\e[0m\e[32mquine-$k\e[0m"
                rm quine-"$k".e
            else
                echo -e "\e[43m???\e[0m\e[33mquine-$k\e[0m"
                cat quine-"$k".e
                echo -e "\e[43m???\e[0m"
            fi
        else
            echo -e "\e[41m!!! ERROR executing quine-$k !!!\e[0m"
        fi
    else
        echo -e "\e[41m!!! ERROR building quine-$k !!!\e[0m"
    fi
    echo
}

if [[ $# -eq 0 ]]; then
    # quine-56 to quine-59 are palindromes, only quine-58 build
    # the last one is empty, penultimate and the one before are backards
    N=55
    # IIRC, quine-00 and quine-11 are for old system, they do not build
    n=2
    while [[ $n -le $N ]]; do
        _do_one "$n"
        n=$(( n + 1 ))
    done
    _do_one 58
else
    for n in "$@"; do
        _do_one "$n"
    done
fi

# ./split_all.sh && ./make_all.sh && ll *.e
