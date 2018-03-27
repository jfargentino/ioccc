#!/bin/bash

export IFS=$'\t'

for file in irred-*; do
	(
		cat $file | cut -f1,2 | while read NAME POLY; do
			( echo -e "&t;\n&E;\n&a;\n&(_d=10000);\n&(p=2);\n&(J=x);\n&(P=$POLY);"; cat testprim.f; echo -e "!!('$NAME OK');\n&q" ) | nice -n20 fermat | grep OK | egrep -o "[][0-9LR.,+-]+"
		done
	) >prim${file#irred} &
done

wait
