#!/bin/bash

cat prim-* | while read NAME; do
	fgrep -w "$NAME" irred-* | cut -f2 | awk -F"	" "{printf(\"$NAME\\t%d\\t\" \$1 \"\\n\", gsub(/+/,\"\",\$1)+1)}"
done | sort -k2 -n
