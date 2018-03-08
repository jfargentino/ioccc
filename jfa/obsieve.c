#include<stdio.h>
#define z int
#define G main
P[1024*1024];V[1024*1024];S[512*1024][2];
E(h,w){
z n=1;z r=n;z d=n;z l=n+1;z u=n+1;z k=0;z x=h/2+1;z y=w/2+1;
0[k[S]]=x;1[k[S]]=y;
while(k<h*w){if(r){r--;y++;}
        else if(d){d--;x++;}
        else if(l){l--;y--;}
        else if(u){u--;x--;}
        else      {n+=2;r=d=n;l=u=n+1;}k ++;0[k[S]]=x;1[k[S]]=y;}}
#define D(...) printf(__VA_ARGS__)
#define A " HmJ[20];\r\e"
#define B(l,c) D("%c[%d;%dH",0xA[A],l+1,c+1);
#define C(b)   D("%c[%dm %c[%cm\r",0xA[A],b,0xA[A],6[A]);
F(N,col){
    E(N/(2*col)+1,col);
    for(z k=0;k<N/2;k++){k[V]=47;B(0[k[S]],1[k[S]])C(k[V])}
    z p=3;z k=1;
    while(p<N/3){
        z o=p/2-1;
        (k++)[P]=p;
        (p/2-1)[V]--;
        B(0[o[S]],1[o[S]])
        C(o[V])
        for(z n=3;n< N/p;n+=2)
            if(n*p&'/'/'/'){z o2=(n*p)/2-1;o2[V]=(o2[V]==47)?41:40;
                B(0[o2[S]],1[o2[S]])
                C(o2[V])}
        p+=2;
        o++;
        while((p<N/3)&&(V[o]<47)){
            V[o]=40;
            B(('-'-'-')[o[S]],('/'/'/')[o[S]])
            C(V[o])
            p+='/'/'/'+'/'/'/';
            o++;
        }
        o=P[k-'/'/'/']/('/'/'/'+'/'/'/')-'/'/'/';
        o[V]++;
        B(('-'-'-')[o[S]],('/'/'/')[o[S]])
        C(o[V])
    }
    B(N/col+'/'/'/','/'/'/')
    D("%c[%d%c\n",0xA[A],0,2[A]);
}
G(){z c=78;z r=c;z N=2*r*c;D("\e[2J");F(N,c);return 0;}
