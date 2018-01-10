#!/bin/bash

N=63
csplit -k -b '-%02d.c' -fself -z self_c.txt '/Author/' "{$N}"
for n in $( seq 0 $N ); do
    if [[ $n -lt 10 ]]; then
        nn='0'$n
    else
        nn=$n
    fi
    sed -i '/\/\/Author.*$/d' "self-$nn.c"
    sed -i '/\/\/Note.*$/d' "self-$nn.c"
    sed -i '/^$/d' "self-$nn.c"
done

