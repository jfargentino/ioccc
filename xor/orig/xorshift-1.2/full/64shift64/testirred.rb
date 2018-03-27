#!/usr/bin/ruby

n = ARGV[0].to_i # number of output files
o = ARGV[1].to_i # output file

f = -1 # output file counter

# Generates all triples of shifts such that a < c
for a in 1..63
	for b in 1..63
		for c in (a+1)..63	
			f = ( f + 1 ) % n
			if f == o; then
				printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", a, b, c)
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('0.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", a, b, c);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('1.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", c, b, a);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('2.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", c, b, a);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('3.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[l]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", a, c, b);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('4.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[r]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", a, c, b);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('5.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[l]^%d);\n", b, a, c);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('6.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
				printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[r]^%d);\n", b, a, c);
				printf("p:=Chpoly([m]);\n")
				printf("irr:=Irred(p);\n")
				printf("!!('7.%d-%d-%d ', p, ' ', irr);\n", a, b, c)
			end
		end
	end
end
