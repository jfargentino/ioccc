??=include <stdarg.h>
??=include <stdio.h>
??=include <stdlib.h>
??=include <string.h>

??=define _ " "
??=define a(b) atoi((b)??(argv??))
??=define c(a) atoi((a)??(b??))
??=define e "echo"
??=define d "%d"
??=define o _ "or" _
??=define n "\n"
??=define s "%s"
??=define sp sprintf
??=define sc strcat
??=ifndef main
??=define main aa
??=endif
char t??(2??)[256] = ??<0??>;
??=define ON(E) sp(0??(t??),e _ d,E)
??=define ONE sp(0??(t??),e _ d o d d,1, 1, 1)
int main (int argc, char ** argv) ??<
    switch(argc)??<
        case 1:sp(0??(t??),e _ s n,0[t]);break;
        case 2:ON(a(1));break;
        default:
        sc(0??(t??),0[argv]);
        while (argc > 3) ??<
            argc --;
            sc(0??(t??),_);
            sc(0??(t??),(argc)[argv]);
        ??>
        sp(1??(t??),_ d,a(2)+a(1));
        sc(0??(t??),1[t]);
        break;
        case 0: ONE; break;
    ??>
    return system(0??(t??));
??>

??=ifdef main
??=undef main
??=define va _start
??=else
??=define aa va
??=endif
int va (int k, ...) ??<
    va_list list;
    va_start(list, k);
    char ** b = va_arg(list, char**);
    switch (k) ??<
        case 2:
        switch (c(1)) ??<
            case 2:
            // recompile to have sum == 1
            //sp(str, "cc -DINTROSPECT=%d %s -o %s\n",
            //         foo, __FILE__, 0??(argv??));
            case 1:
            k=0;
        ??>
    ??>
    return aa (k, b);
??>

