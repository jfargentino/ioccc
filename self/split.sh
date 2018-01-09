#!/bin/bash

sed -i 's/^Author/\/\/Author/' self_c.txt
sed -i 's/^Notes/\/\/Notes/' self_c.txt
N=63
csplit -k -b '-%02d.c' -fself -z self_c.txt '/Author/' {$N}

