#!/bin/bash -e

if [[ "$@" == "" ]]; then
	echo "$(basename $0) POWER" 1>&2
	exit 1
fi

export IFS=$'\t'

while read NAME WEIGHT POLY; do
		echo -en "$NAME\t"
		echo -e "&t;\n&E;\n&a;\n&(_d=10000);\n&(p=2);\n&(J=x);\n&(P=$POLY);\np:=x;\nfor i=1,$1 do p:=p*p; od;\n!!('OK', p)\n&q" \
			| nice -n20 fermat | grep OK | cut -d' ' -f2- | ${0%.sh}.py
done
