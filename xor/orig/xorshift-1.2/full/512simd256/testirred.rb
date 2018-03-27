#!/usr/bin/ruby

require "rational"

n = ARGV[0].to_i # number of output files
o = ARGV[1].to_i # output file

f = -1 # output file counter

for p in [0,1,2,3,4,5,6,7].permutation do
	good = true
	for i in 0..7 do
		if 7^p[i^7] != p[i] or i/4 == p[i]/4; then good = false; break; end
	end
	if ! good; then next; end;

	# Generates all triples of shifts
	# shift < 64: 64-bit lane shift
	# shift >= 64: 128-bit lane byte shift of (shift - 63) * 8
	for a in 1..78 do # Left shift
		for b in 1..78 do # Left rotate
			for c in 1..78 do # Left shift
				if b < 64; then bb = 64 - b else bb = 63 + (16 - (b - 63)) end

				for dir_a in 0..1 do
					for dir_b in 0..1 do
						for dir_c in 0..1 do

							f = ( f + 1 ) % n
							if f == o; then
								printf("[a]:=0;\n");
								printf("[b]:=0;\n");
								printf("[c]:=0;\n");
								printf("[t]:=0;\n");

								if a < 64; then printf("for p=0,3 do for i = 0,63-%d do a[p*64+i+%d,p*64+i]:=1; od; od;\n", a, a)
								else 
									sh = ( a - 63 ) * 8
									printf("for i=0,127-%d do a[i+%d,i]:=1; a[128+i+%d,128+i]:=1; od;\n", sh, sh, sh)
								end
								if b < 64; then printf("for p=0,3 do for i = 0,63-%d do b[p*64+i+%d,p*64+i]:=1; od; od;\n", b, b)
								else
									sh = ( b - 63 ) * 8
									printf("for i=0,127-%d do b[i+%d,i]:=1; b[128+i+%d,128+i]:=1; od;\n", sh, sh, sh)
								end
								if bb < 64; then printf("for p=0,3 do for i = 0,63-%d do b[p*64+i,p*64+i+%d]:=1; od; od;\n", bb, bb)
								else
									sh = ( bb - 63 ) * 8
									printf("for i=0,127-%d do b[i,i+%d]:=1; b[128+i,128+i+%d]:=1; od;\n", sh, sh, sh)
								end
								if c < 64; then printf("for p=0,3 do for i = 0,63-%d do c[p*64+i+%d,p*64+i]:=1; od; od;\n", c, c)
								else
									sh = ( c - 63 ) * 8
									printf("for i=0,127-%d do c[i+%d,i]:=1; c[128+i+%d,128+i]:=1; od;\n", sh, sh, sh)
								end

								# Conjugate permutation to compensate for little-endianness.
								for s in 0..7 do
									printf("for i = 0,31 do t[%d+i,%d+i]:=1; od;\n", (p[s] ^ 7) * 32, (s ^ 7) * 32)
								end

								if dir_a != 0; then printf("[a]:=Trans[a];\n") end
								if dir_b != 0; then printf("[b]:=Trans[b];\n") end
								if dir_c != 0; then printf("[c]:=Trans[c];\n") end

								printf("[q]:=[0];\n")
								printf("[m]:=[a] + [1];\n")
								printf("for i = 0,255 do for j = 0,255 do q[i,j]:=m[i,j]; od; od;\n")
								printf("[m]:=[a] + [1] + [t];\n")
								printf("for i = 0,127 do for j = 0,255 do q[256+i,j]:=m[i,j]; od; od;\n")
								printf("for i = 0,255 do for j = 0,127 do q[i,j+256]:=b[i,j]; od; od;\n")
								printf("[m]:=[b] + [c];\n")
								printf("for i = 0,127 do for j = 0,127 do q[256+i,256+j]:=m[i,j]; od; od;\n")

								printf("if Det[q] then [m]:=([1]*x + [a] + [1])*([1]*x + [b] + [c]) + ([a] + [1] + [t])*[b]; p:=Det[m]; irr:=Irred(p); !!('%d%s-%d%s-%d%s+[%s] ', p, ' ', irr); fi;\n", a, dir_a == 0 ? "L" : "R", b, dir_b == 0 ? "L" : "R", c, dir_c == 0 ? "L" : "R", p.join(","))
							end
						end
					end
				end
			end
		end
	end
end
