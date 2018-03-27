#!/usr/bin/python

import sys
from collections import Counter

n = int(sys.argv[1]) - 1
if n < 0:
    raise ValueError, "Equidistribution dimension must be positive"

output = map(lambda x: x.strip(), sys.stdin.readlines())
tuples = len(Counter(output))

concat = output

for i in range(n):
    output = output[1:] + output[:1]
    concat = zip(concat, output)

counter = Counter(concat)

print "Number of tuples: %d (expected: %d)" % (len(counter), tuples**(n+1))
print "List of counts: %s" % Counter(counter.values())
