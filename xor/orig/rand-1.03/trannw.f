C trannw.f - test routine for rannw.f - version 1.02 of 28 October 2001
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
C The program takes about 21 sec to run on a 300 Mhz Pentium II under
C linux, and the output file on unit 11 is about 24 MByte.
C
C R. P. Brent, last revised 20011028
C
C Test program starts here.
C
C       implicit none
        integer WKMAX, BUFMAX
C
C Recommended values are WKMAX = 60000 and BUFMAX = 1000.
C Smaller or larger values of WKMAX and BUFMAX may be used if desired.
C Minimal values are WKMAX = 1350, BUFMAX = 1
C
        parameter (WKMAX = 60000)
        parameter (BUFMAX = 1000)
C
        integer ix, n, nwork, j, rkt, k, kk, kkk
        integer hx
        double precision da(BUFMAX), dwork(WKMAX), dx
        double precision am, sd, qnorm
        character hex(16), line(80)
        data hex /'0','1','2','3','4','5','6','7',
     $            '8','9','a','b','c','d','e','f'/
C
        print *, ' This is trannw version 1.02'
        print *, ' Most output is on unit 11'
        print *, ' Seed (positive), nwork, mean, standard deviation ? '
        read *, ix, nwork, am, sd
        if (ix .le. 0) then
          print *, ' Error 1 in trannw: seed ', ix, ' not positive'
          stop
          endif
        print *, ' Using seed ', ix
        if (nwork .gt. WKMAX) then
          print *, ' Warning 1 in trannw: nwork too large, using WKMAX'
          nwork = WKMAX
          endif
        print *, ' Using nwork ', nwork
        print *, ' Using mean ', am 
        print *, ' Using standard deviation ', sd
        if (sd .eq. 0d0) then
          print *, ' Error 2 in trannw: sd = 0'
          stop
          endif
        n = BUFMAX
        print *, ' Using n ', n, ' in first call to rannw'
C First call - here ix is positive, returned as zero
        call rannw (am, sd, ix, da, n, dwork, nwork)
        if (ix .ne. 0) then
          print *, ' Error 3 in trannw: rannw returned nonzero ix=', ix
          stop
          endif
        n = min (n, 10)
        print *, ' First few normal numbers follow '
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
        call rannw (am, sd, ix, da, n, dwork, nwork)
        do 60 k = 1, 10
        dx = da(k)
C
C Convert to uniform numbers and write in hex format on unit 11
C for input to Marsaglia's asc2bin program
        dx = qnorm((dx - am)/sd)
C Now dx should be uniform in (0, 1)
        if ((dx .lt. 0d0) .or. (dx .ge. 1d0)) then
          print *, ' Error 4 in trannw: possible error in qnorm'
          stop
          endif
C Now convert to hexadecimal
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
        print *, ' Last few normal numbers follow '
        do 90 j = 1, n
90      print 20, da(j)
        print *, ' Use asc2bin and Diehard to test output file'
        end
C
        function qnorm(x)
        double precision qnorm, x
C
C Computes Q(x) = tail of normal distribution
C with absolute error < 7.5D-8; see A&S 26.2.17.
C
        double precision q, t, z
        double precision qmin, qmax
        double precision b0, b1, b2, b3, b4, b5, pp
        data b0 /0.2316419d0/
        data b1 /0.319381530d0/
        data b2 /-0.356563782d0/
        data b3 /1.781477937d0/
        data b4 /-1.821255978d0/
        data b5 /1.330274429d0/
C       pp = 1/sqrt(2*pi)
        data pp /0.398942280401433d0/
        z = pp*dexp(-0.5d0*x*x)
        t = (1.0d0/(1.0d0 + b0*dabs(x)))
        q = z*t*(b1 + t*(b2 + t*(b3 + t*(b4 + t*b5))))
        if (x .lt. 0d0) q = 1.0d0 - q
        qnorm = q
        return
        end

C End of trannw.f - add rannw.f, ranut.f here
C =====================================================================
