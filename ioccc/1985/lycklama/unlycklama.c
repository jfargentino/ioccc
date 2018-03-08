main(){
    char c=0,d,e,f[80];
    goto LABEL1;
LABEL:
    e=79;
LABEL_0:
    write(1, f, (unsigned)(d=(c-1 < e ? c-1 : e)));
    for(; d; write(1,"\b",1u), d--);
    write(1," ",1u);
    if(--e) goto LABEL_0;
    write(1,"\n",1u);
LABEL1:
    if(c=read(0,f,80)) goto LABEL;
}
