&t;
&E;
&a;
&(_d=10000);
Array sl[64,64], sr[64,64], rl[64,64], rr[64,64], m[64,64];
&(p=2);
&(J=x);
[sl]:=0;
[sr]:=0;
for i = 0,62 do sl[i+1,i]:=1; sr[i,i+1]:=1; od;
[rl]:=[sl];
[rr]:=[sr];
rl[0,63]:=1;
rr[63,0]:=1;
