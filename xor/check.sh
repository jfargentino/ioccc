#!/bin/bash

#make check
if [ ! -e ./uuid4 ]; then
    make uuid4
fi
if [ ! -e orig/uuid4/example/example ]; then
    make ref
fi
if [ ! -e ./marsaglia ]; then
    make marsaglia
fi
if [ ! -e ./marsaglia_ref ]; then
    make marsaglia_ref
fi

#orig/uuid4/example/example 2> .SEED 1> .UUID_REF
#SEED0=$(awk '{print $1}' .SEED)
#SEED1=$(awk '{print $2}' .SEED)
#./uuid4 -s "$SEED0" "$SEED1" > .UUID
#cat .UUID .UUID_REF
#diff .UUID .UUID_REF

./marsaglia_ref 10 > .MARS_REF
./marsaglia     10 > .MARS
head .MARS .MARS_REF
diff .MARS .MARS_REF
tail .MARS .MARS_REF
