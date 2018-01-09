//Author:Patrik Lundin (lundin@ludd.luth.se)
Note: When I wrote it, the point was to try to do it
without using printf, and with <cr>:s.

void a(char*b,int d,int e,int f){char*c=b;for(;*c;c++){if(!d&*c==68)putchar(
92),putchar('\n');if(!d&*c==92)putchar(92);if(*c==d)a(b,0,0,0);else putchar(
*c==e?34:*c==f?'\n':*c);}}main(){char p[]=/*
andelion '94 */
"void a(char*b,int d,int e,int f){char*c=b;for(;*c;c++){if(!d&*c==68)putchar(\
D92),putchar('\\n');if(!d&*c==92)putchar(92);if(*c==d)a(b,0,0,0);else putchar(\
D*c==e?34:*c==f?'\\n':*c);}}main(){char p[]=/* \
Dandelion '94 */\
DCAC;a(p,65,67,68);}";a(p,65,67,68);}


