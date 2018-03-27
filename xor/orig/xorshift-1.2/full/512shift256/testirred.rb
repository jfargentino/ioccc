#!/usr/bin/ruby

require "rational"

n = ARGV[0].to_i # number of output files
o = ARGV[1].to_i # output file

f = -1 # output file counter

# Generates all triples of shifts such that a + b <= 256 and a,b are coprime
for a in 21..255 do 
	for b in 1..(256-a) do 
		if a.gcd(b) != 1; then next; end
		for c in 1..255 do 
			f = ( f + 1 ) % n
			if f == o; then
				printf("[m]:=[1]*(x^2) + ([1]+[l]^%d)*([1]+[r]^%d) + ([1]+[r]^%d)*x;\n", a, b, c )
				printf("p:=Det[m];\n");
				printf("irr:=Irred(p);\n")
				printf("!!('%d-%d-%d ', p, ' ', irr);\n", a, b, c)
			end
		end
	end
end
