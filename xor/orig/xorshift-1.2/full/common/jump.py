#!/usr/bin/python

import sys
import re

params = sys.stdin.readline().strip()

mask = [0]*64 # Large enough for 2^4096
maxmask = 0

for m in re.split("\s+\+\s+",params):
    if m == "1":
        power = 0
    elif m == "x":
        power = 1
    else:
        power = int(m.split("^")[1])

    maxmask = max(power / 64, maxmask)
    mask[power / 64] |= 1 << (power % 64)

out = "{ "
for i in range(maxmask+1):
    out += "0x%016x, " % mask[i]

print out[:-2] + " }"
