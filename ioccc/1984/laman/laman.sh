#!/bin/bash

for x in `seq 0 "$1"`; do 
    ./laman ${x}
    sleep 0.1
    clear
done

