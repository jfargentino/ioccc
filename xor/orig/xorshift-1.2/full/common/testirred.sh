#!/bin/bash

if [[ "$@" == "" ]]; then
	echo "$(basename $0) THREADS" 1>&2
	exit 1
fi

for ((i=0; i<$1; i++)); do 
	rm -f fifo-$i
	mkfifo fifo-$i
	(cat testirred.f; ./testirred.rb $1 $i ; echo '&q') >fifo-$i &
	# The egrep pattern must match 0.1-2-3, 1-2-3, 1-2-[0,1,2,3], 1-2-3+[0,1,2,3], etc.
	echo -e "&(R='fifo-$i');\n&q" | nice -n20 stdbuf -oL fermat | stdbuf -oL egrep "^[][0-9LR,.+]+-[][0-9LR,.+]+-[][0-9LR,.+]+ " | stdbuf -oL sed -e 's/ [ ]\+/	/g' | stdbuf -oL egrep "	1\$">irred-$i &
done

wait

for ((i=0; i<$1; i++)); do rm -f fifo-$i; done
