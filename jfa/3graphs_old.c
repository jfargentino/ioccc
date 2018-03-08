??=include<stdio.h>

/*
int main (void) ??<
    unsigned char a??(1??) = ??< 0x5A ??> ;
    unsigned char b??(1??) = ??< ??- 0x5A ??> ;
    unsigned char c??(1??) = ??< a??(0??) ??! b??(0??) ??>;
    return printf ("%02X %%02X\n", a??(0??) ??' b??(0??), c??(0??));  
??>
*/

??=define if while
??=define else

// Native ops
??=define NOT(x)   ??-(x)
??=define  OR(x,y) (x)??!(y)
??=define XOR(x,y) (x)??'(y)
??=define AT(array,index) (array)??(index??)
// Now compose
??=define AND(x,y) NOT(OR(NOT(x),NOT(y)))
??=define ADD(x,y) XOR(XOR(x,y),AND(x,y)<<1)

#define and(x,y) (~((~(x))|(~(y))))
#define add(x,y) (((x)^(y))^((~((~(x))|(~(y))))<<1))

int main (void) ??<
    unsigned char a??(1??) = ??< 0x5A ??>;
    unsigned char b??(1??) = ??< NOT(0x5A) ??>;
    unsigned char AT(c,1) = ??< XOR( a??(0??), b??(0??) ) ??>;
    //return printf ("%02X %02X\n", AT(c, 0), AND(AT(a,0), AT(b,0)));  
    return printf ("%d\n", ADD(6, 8));
??>

// #!/bin/bash
// sed 's/\\/??\//g' | sed 's/#/??=/g'  | sed "s/\^/??\'/g"\
//                   | sed 's/|/??!/g'  | sed 's/~/??-/g'  \
//                   | sed 's/{/??</g'  | sed 's/}/??>/g'  \
//                   | sed 's/\[/??(/g' | sed 's/\]/??)/g' \
//                 
//
//           3F ?
//     23 #  3D =
//     5B [  28 (
//     5C \  2F /
//     5D ]  29 )
//     5E ^  27 '
//     7B {  3C <
//     7C |  21 !
//     7D }  3E >
//     7E ~  2D -
// 
