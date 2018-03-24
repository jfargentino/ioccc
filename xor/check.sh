#!/bin/bash

if [ ! -e ./uuid4 ]; then
    make uuid4
fi

if [ ! -e orig/uuid4/example/example ]; then
    make ref
fi

orig/uuid4/example/example 2> .SEED 1> .UUID_REF

SEED0=$(awk '{print $1}' .SEED)
SEED1=$(awk '{print $2}' .SEED)
./uuid4 -s "$SEED0" "$SEED1" > .UUID
diff .UUID .UUID_REF

