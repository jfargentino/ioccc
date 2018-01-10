#!/bin/bash

N=63
csplit -k -b '-%02d.c' -fquine -z self_c.txt '/Author/' "{$N}"
for n in $( seq 0 $N ); do
    if [[ $n -lt 10 ]]; then
        nn='0'$n
    else
        nn=$n
    fi
    sed -i '/\/\/Author.*$/d' "quine-$nn.c"
    sed -i '/\/\/Note.*$/d' "quine-$nn.c"
    sed -i '/^$/d' "quine-$nn.c"
done

