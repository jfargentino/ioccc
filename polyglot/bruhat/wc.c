#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#define open(a,b) open(b,a)
#define $ARGV argv
#define $i i
#define x : /* aren't four #define way too much?
               unshift @ARGV, $_ = $ARGV[0]; "*/
main(int argc, char *argv[]) { // "; {
  int m=1, i[14]; char * pp; int p=-1;
  int q, F=3; char * qq = "Hello\, world!\n";
      i[12]=537463307; i[13]=3085; //,; $_ = "" if(length!=2);
  if(m+-p?(argc>1&&!strcmp(argv[1],"-p"))?p+i? 1 : 1 x 0 x 0) {
    printf(qq/*\bThe Perl Journal\n/#*/
          ); exit(0); }
  qq="=;#"; argv[0][0]='\0'; memset(i,0,48);
  $i[10]=($i[11]=(q/*\b/&&scalar@ARGV))-1;#*/=0) + argc)-1;
  do{
    if($i[11]<2) { $i[10]=1; q/*/&&*F=*STDIN;#*/=F=0;
    } else { open(O_RDONLY, $ARGV[$i[11]-$i[10]]);//; *F=*O_RDONLY;
    }
    while(read(F, $i, 1)>0) {
      ++$i[4]^(q=/*.=,$_=$i);#*/0); pp=i;
      $i[3]+=m=( *pp^0x0A)?/*\n=;#*/0:1; for(qq=&i[12];*qq;*pp^*qq++||(q=1));
      if(m=/*[ 	\n\f\r\xB]=#*/q
        ) { if($i[1]){$i[$i[1]]++; $i[1]=0; }} else { $i[1]=2;}
    }
    if($i[1]){$i[$i[1]]++;};
    printf("%7d %7d %7d %s\n",$i[3],$i[2],$i[4],$ARGV[$i[11]-$i[10]]);
    close(F);
    if($i[11]>2){for($i[1]=2;$i[$i[1]+4]+=$i[$i[1]];$i[1]++){$i[$i[1]]=0;};$i[1]=0;}
  } while(--$i[10]);
  if($i[11]>2) { printf("%7d %7d %7d total\n",$i[7],$i[6],$i[8]); }
}
