C tranut.f - test routine for ranut.f - version 1.03 of 3 January 2002
C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C  Copyright (C) 2001 R. P. Brent.                                     C
C                                                                      C 
C  This program is free software; you can redistribute it and/or       C
C  modify it under the terms of the GNU General Public License,        C
C  version 2, June 1991, as published by the Free Software Foundation. C
C  For details see http://www.gnu.org/copyleft/gpl.html .              C    
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C
C This program produces hex output for Marsaglia's asc2bin
C program (so can run Diehard tests). For information on Marsaglia's
C Diehard programs see:
C
C   http://stat.fsu.edu/~geo/, ftp://stat.fsu.edu/pub/diehard/
C   ftp://stat.fsu.edu/pub/diehard/index.html
C
C The program takes about 18 sec to run on a 300 Mhz Pentium II under
C linux, and the output file on unit 11 is about 24 MByte.
C
C R. P. Brent, last revised 20011028
C
C Test program starts here.
C
C       implicit none
        integer WKMAX, BUFMAX
C
C Recommended values are WKMAX = 24000 and BUFMAX = 2*WKMAX, 
C which uses 563KB memory and permits r = 23209.
C
C Smaller or larger values of WKMAX and BUFMAX may be used if desired.
C Increase WKMAX to 3021377+7 = 3021384 if extremely long period
C generator is required (this is not recommended because of the
C large space requirement and slow initialisation).
C
        parameter (WKMAX = 24000)
        parameter (BUFMAX = 2*WKMAX)
C
        integer ix, n, nwork, j, rkt, k, kk, kkk
        integer hx
        double precision da(BUFMAX), dwork(WKMAX), dx
        character hex(16), line(80)
        data hex /'0','1','2','3','4','5','6','7',
     $            '8','9','a','b','c','d','e','f'/
C
C Set testlow to .true. to test low-order 32 bits,
C otherwise test high-order 32 bits (of nw, typically 49)
C
        logical testlow
        data testlow /.false./
C
        print *, ' This is tranut version 1.03'
        print *, ' Most output is on unit 11'
        print *, ' Seed (positive), nwork ? '
        read *, ix, nwork
        if (ix .le. 0) then
          print *, ' seed must be positive'
          stop
          endif
        print *, ' Using seed ', ix
        if (nwork .gt. WKMAX) then
          print *, ' nwork too large, using WKMAX'
          nwork = WKMAX
          endif
        print *, ' Using nwork ', nwork
        n = BUFMAX
        print *, ' Using n ', n, ' in first call to ranut'
C First call - here ix is positive, returned as zero
        call ranut (ix, da, n, dwork, nwork)
        if (ix .ne. 0) then
          print *, ' error in tranut: ranut returned nonzero ix = ', ix
          stop
          endif
        print *, ' r = ',int(dwork(1)), ', s = ', int(dwork(1)-dwork(2))
        print *, ' alpha = ', int(dwork(3)), ', beta = ', int(dwork(4))
        if (testlow) then
          print *, ' testing low 32 bits'
        else
          print *, ' testing high 32 bits'
          endif
        n = min (n, 10)
        print *, ' First few numbers follow '
        do 10 j = 1, n
10      print 20, da(j)
20      format (1x, f12.8)
C
C Generate 3000000 random numbers in 300000 lines of 10 each for 
C testing by Marsaglia's Diehard package
C
        rkt = 300000
        n = 10
        print *, ' Generating ', n*rkt, ' numbers, output on unit 11'
        print *, ' .. this will take a while - please be patient'
        do 80 j = 1, rkt
        call ranut (ix, da, n, dwork, nwork)
        do 60 k = 1, 10
        dx = da(k)
C
        if (testlow) then
C Test low 32 of nw = 49 bits (see below)
          dx = (2**(49-32))*dx
          dx = dx - int(dx)
          endif
C
C Convert to hex output for input to Marsaglia's asc2bin program
        do 50 kk = 1, 8
          kkk = kk + 8*(k-1)
          hx = int(16.0d0*dx)
          dx = 16.0d0*dx - hx
          line(kkk) = hex(hx+1)
50        continue
60      continue
        write (11, 70) line
70      format (80a1) 
80      continue
        print *, ' Last few numbers follow '
        do 90 j = 1, n
90      print 20, da(j)
        print *, ' Use asc2bin and Diehard to test output file'
        end
C
C End of tranut.f - add ranut.f and associated routines here
C =====================================================================
