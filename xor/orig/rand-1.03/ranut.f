C ranut.f - uniform random number generator, version 1.03 of 3 Jan 2002
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
        subroutine ranut (ix, da, n, dwork, nwork)
C       implicit none
        integer ix, n, nwork
        double precision da(*), dwork(*)
C
C Returns n uniformly distributed random numbers in da(1) .. da(n).
C The numbers are uniformly and independently distributed in [0, 1).
C
C ix is a nonzero seed provided by the caller.
C On the first call, ix should be positive.  It is returned as zero
C and should remain zero for subsequent calls.
C
C da(*) is a double-precision array of dimension at least n.
C ranut fills da(1), da(2), ... , da(n) with pseudo-random number
C uniformly distributed in [0, 1).
C da need not be preserved between calls (i.e. da(1) .. da(n) can
C be modified by the caller).
C
C n is the number of random numbers to return.
C The dimension of da must be at least n.
C For efficiency n should be large.
C It is recommended that n should be at least 2*nwork.
C n may be different on each call to ranut.
C If n is not positive, no random numbers are returned.
C
C dwork(*) is a double-precision array of dimension at least nwork
C used as a work area and to save state information.
C dwork(1) .. dwork(nwork) must be preserved between calls to ranut.
C
C nwork must be at least 388 if n < 254,
C            or at least 134 if n > 253.
C
C For efficiency and the best statistical properties
C nwork should be large (up to a maximum of 3021384).
C
C Recommended values are nwork = 24000 and n = 2*nwork, which uses
C about 563KB memory and permits a lag of r = 23209 (see below).
C
C The method used is an additive "generalized Fibonacci" recurrence
C with lags r > s > 0 (see further comments below).  This is very fast, 
C but for the best statistical properties it may be desirable to combine
C the results with the output of another generator (e.g. by addition 
C mod 1).
C
C In some applications it is inconvenient that the random
C numbers da(j) returned may occasionally be zero.
C To avoid this problem, use (1.0d0 - da(j)) instead of da(j).
C If it is necessary to avoid both 0 and 1, use
C da(j) + small, where small = 0.5d0**(nw+2) and nw is 
C usually 49 (see below).
C
C Several subroutines follow. The only routine of concern to the user is
C
C ranut  - returns array of uniform random numbers,
C          also performs initialization on first call.
C
C The user need not be concerned with the following routines,
C which are called (directly or indirectly) by ranut
C
C initut - performs initialization.
C ranuut - returns array of random numbers, size specified by caller.  
C ran2ut - slight variation on ranuut, called by ranut, ranuut.
C fil2ut - returns fixed-size batch of random numbers, called by initut.
C skiput - called by initut.
C sqshut - called by skiput.
C
C R. P. Brent, last revised 20011028.
C
        integer r, s, alpha, beta, lut, nw
C
C Following is a table of 25 possible pairs (r, s) which give close to
C the maximal period possible for given r. See comments in initut.
C On the first call we select the largest r possible for given nwork,
C and the corresponding value of s (which may be replaced by r-s).
C
        integer tabsiz, rtab(25), stab(25)
        integer j
        logical check
C
        data tabsiz /25/
C
        data rtab / 127,    258,    521,    607,   1279,    2206,  
     $             2281,   3217,   4261,   4423,   9689,    9944, 
     $            11219,  19937,  21704,  23209,  44497,   86245, 
     $           110503, 132049, 216103, 756839, 859433, 1257790,
     $          3021377/
C       
        data stab /  30,     83,    168,    273,    418,     355,  
     $             1029,    576,   1806,   2098,   4187,    1077, 
     $              227,   9842,   7587,   9739,  21034,    2288, 
     $            53719,  52549,  42930, 279695, 170340,   74343,
     $           361604/
C
C nw is the number of bits to use in a floating-point word.
C nw+4 should not exceed the number of bits in the floating-point
C fraction. 
C
C Default value is nw = 49 because this works on machines with 
C IEEE standard floating-point arithmetic.  Decrease if necessary.
C
        data nw /49/
C
        if (ix .ne. 0) then
          j = tabsiz + 1
10        j = j - 1
          if (j .le. 0) then
            print *, ' Error 1 in ranut - nwork too small'
            stop
            endif
          r = rtab(j)
          s = stab(j)
C It is convenient to assume wlog that s .ge. r-s.
          if (s .lt. (r-s)) then
            s = r - s
            endif
          if (.not. (((nwork .ge. r+7) .and. (n .ge. 2*r)) .or.
     $                (nwork .ge. 3*r+7))) go to 10
C
C Choose alpha = 1 for speed if r is sufficiently large,
C otherwise alpha > 1 for good statistical properties.
C Need alpha + beta at most 16 to avoid losing more than 4 bits
C and alpha, beta odd.
C
          if (r .gt. 10000) then
            alpha = 1
            beta  = 13
          else
            alpha = 5
            beta  = 7
            endif
C
C ix should be nonnegative
C
          if (ix .lt. 0) then
            print *, ' Error 2 in ranut - negative seed'
            stop
            endif
C
C Initialize dwork using da (if large enough) for temporary space,
C otherwise high end of dwork.
C
          if (n .ge. 2*r) then
            call initut (r,s,alpha,beta,nw,ix,lut,dwork(7),da)
          else
            call initut (r,s,alpha,beta,nw,ix,lut,dwork(7),dwork(r+8))
            endif
C
C         print *, ' Using nw ', nw
C
C Save (r, s, alpha, beta, lut) in first 5 words of dwork
C
          dwork(1) = dfloat(r)
          dwork(2) = dfloat(s)
          dwork(3) = dfloat(alpha)
          dwork(4) = dfloat(beta)
          dwork(5) = dfloat(lut)
C
C For checking purposes, save r in words 6 and r+7
C
          dwork(6) = dfloat(r)
          dwork(r+7) = dfloat(r)
C
C Set ix = 0 for subsequent calls
C
          ix = 0
          endif
C
C Except on first call (or restart with ix > 0) the initialization
C above is skipped.
C
C Check that r saved in dwork(1) and dwork(6) consistent
        if (dwork(6) .ne. dwork(1)) then
          print *, ' Error 3 in ranut - work array inconsistent'
          stop
          endif
        r = int(dwork(1))
C More checks to see if dwork overwritten or not initialized
C This may indicate that first call to ranut has ix = 0
        if ((r .lt. rtab(1)) .or. (r .gt. rtab(tabsiz))) then
          print *, ' Error 4 in ranut - work array not initialized ?'
          stop
          endif
        if (dwork(r+7) .ne. dwork(1)) then
          print *, ' Error 5 in ranut - work array not initialized ?'
          stop
          endif
        s = int(dwork(2))
        if ((r .le. s) .or. (r .ge. 2*s)) then
          print *, ' Error 6 in ranut - work array overwritten ?'
          stop
          endif
        alpha = int(dwork(3))
        beta  = int(dwork(4))
        if ((alpha .le. 0) .or. (beta .le. 0) .or.
     $      (mod(alpha,2) .eq. 0) .or. (mod(beta,2) .eq. 0) .or.
     $      (alpha + beta .gt. 16)) then
          print *, ' Error 7 in ranut - work array overwritten ?'
          stop
          endif
        lut = int(dwork(5))
        if ((lut .lt. 0) .or. (lut .ge. r)) then
          print *, ' Error 8 in ranut - work array overwritten ?'
          stop
          endif
C
C No errors detected, so call ranuut or ran2ut to generate random
C numbers. Separate routines for alpha .eq. 1 and alpha .ne. 1 so
C some optimisations can be performed.
C
        if (alpha .eq. 1) then
          call ranuut (r,s,alpha,beta,dwork(7),dwork(7),lut,n,da,da,da)
        else
          call ran2ut (r,s,alpha,beta,dwork(7),dwork(7),lut,n,da,da)
        endif
C
C Save lut for next call
C
        dwork(5) = dfloat(lut)
        return
        end
C
C The routines initut, ranuut, ran2ut, fil2ut, skiput, sqshut
C are called (directly or indirectly) by ranut
C
        subroutine initut (r, s, alpha, beta, nw, seed, lastut, x, xb)
C       implicit none
        integer r, s, alpha, beta, nw, seed, lastut
        double precision x(*), xb(*)
C
C Initialization routine.
C
C r and s define lags (see below).
C
C alpha and beta are small odd integers used as multipliers.
C
C nw is number of bits to be used in floating-point word.
C nw = 0 means use the maximum number possible;
C if nw is specified too large then the maximum possible will be used.
C The number actually used is returned in nw.
C Assuming alpha+beta <= 16, can take nw = 49 on IBM PC with 80x87 fl pt.
C
C seed is a positive integer.
C
C x(r) and xb(2*r) are working arrays.
C xb could be logical but we have made it double precision
C so the output buffer of ranuut can be used for it
C (the dimension of this buffer must be at least 2*r).
C
C lastut and x(1..r) must be preserved between calls to ranuut.
C
C The period of the generator is at least half of the maximum possible
C value (2^r - 1)*2^(nw-1)
C and the period of the least significant bit is at least 2^(r - 1),
C because the associated polynomials are either primitive or have
C a large primitive factor.
C
C For theory, see R. P. Brent, "On the Periods of Generalized Fibonacci
C Recurrences", Mathematics of Computation 63 (1994), 389-401.
C
C Some pairs (r, s) which give the
C maximal period (2^r - 1)*2^(nw-1) are:
C
C (127, 97),    (258, 175)      (smaller values are not recommended)
C (521, 353),   (607, 334)
C (1279, 861),  (2281, 1252)    (recommended for moderate-scale use)
C (3217, 2641), (4423, 2325)
C (9689, 5502)                  (the largest given by Zierler)
C (19937, 10095)                
C (23209, 13470)                (recommended for large-scale use)
C
C                               The following are larger than necessary in
C                               most applications, but included for the
C                               sake of completeness
C
C (44497, 23463)                (Kurita et al)
C (110503, 56784)               (Heringa et al)
C (132049, 79500)               (Heringa et al)
C (756839, 477144)              (Brent et al, June 2000)
C (859433, 689093)              (Brent et al, June 2000)
C (3021377, 2659773)            (Brent et al, August 2000)
C
C The following (r, s) do not give quite the maximal period but they
C do get within a factor of 2, which is close enough. 
C [Brent, Larvala and Zimmermann, unpublished, 2001].
C
C (2203+3, 355)                 Period 7(2^2203-1)*2^(nw-1)
C (4253+8, 1806)                Period 255(2^4253-1)*2^(nw-1)
C (9941+3, 1077)                Period 7(2^9941-1)*2^(nw-1)
C (11213+6, 227)                Period 63(2^11213-1)*2^(nw-1)
C (21701+3, 7587)               Period 7(2^21701-1)*2^(nw-1)
C (86243+2, 2288)               Period 3(2^86243-1)*2^(nw-1)
C (216091+12, 42930)            Period 31*127*(2^216091-1)*2^(nw-1)
C (1257787+3, 74343)            Period 7(2^1257787-1)*2^(nw-1)
C
C See R. P. Brent, S. Larvala and P. Zimmermann,
C "A fast algorithm for testing irreducibility of trinomials mod 2"
C Report PRG TR-13-00, Oxford University Computing Laboratory,
C 30 December 2000 (and the references given there).
C http://www.comlab.ox.ac.uk/work/richard.brent/pub/pub199.html
C
C Note that s < r/2 may be replaced by r-s.
C
C skiput is called to skip forward seed*2^90 terms in the sequence
C so subsequences of length less than 2^90 will not overlap
C if started with distinct seeds. 2^90 > 10^27 so this should suffice.
C r should be at least 122 = 90 + 32 (assuming 32-bit integers).
C
C R. P. Brent, last revised 20011028.
C
        integer j, k, nw2
        double precision eps, minx, temp1, temp2
C Test that arguments are sensible
        if ((s .le. 0) .or. (r .le. s) .or. (2*s .le. r)) stop
        if (nw .lt. 0) stop
        if (seed .le. 0) stop
        if (r .lt. 122) then
          print *, ' Error 1 in initut - r = ', r, ' is too small'
          stop
          endif
        if ((alpha .le. 0) .or. (beta .le. 0)) stop
        if ((mod(alpha,2) .eq. 0) .or. (mod(beta,2) .eq. 0)) stop
        if (alpha + beta .gt. 16) then
          print *, ' Error 2 in initut - alpha + beta > 16'
          stop
          endif
        eps = 1.0d0
        nw2 = 0
        temp1 = dfloat(alpha + beta - 1)
10      eps = 0.5d0*eps
        if (eps .eq. 0.0d0) then
          print *, ' Error 3 in initut - eps has underflowed'
          stop
          endif
        nw2 = nw2 + 1
        temp2 = temp1 + eps
        if ((temp2 - temp1 .eq. eps) .and.
     $    ((nw .eq. 0) .or. (nw2 .lt. nw))) go to 10
        if (temp2 - temp1 .ne. eps) then
20        eps = 2.0d0*eps
          nw2 = nw2 - 1
          temp2 = temp1 + eps
          if (temp2 - temp1 .ne. eps) go to 20
          endif
        nw = nw2
C See above regarding constant 90
        call skiput (r, s, seed, 90, x, xb, eps)
C Initialize lastut for use by ranuut.
        lastut = 0
C Because only least significant bits set, need to
C discard O(nw*r) numbers.
        j = 0
30      if (j .gt. 100*nw2) then
C The following may indicate that array dimensions are too small
          print *, ' Error 4 in initut - too many calls to fil2ut'
          stop
          endif
        call fil2ut (r, s, alpha, beta, x, x)
        j = j + 1
        if (x(1) .lt. 0.1d0) go to 30
C Following probably not necessary (unless seed = 0 permitted)
        minx = 1.0d0
        do 40 k = 1, r
40      minx = min (minx, x(k))
        if (dfloat(r)*minx .lt. 0.5d0) go to 30
C       print *, j, ' calls to fil2ut'
C Iterate a few more times for safety (increased to 30, was 10)
        do 50 j = 1, 30
50      call fil2ut (r, s, alpha, beta, x, x)
        return
        end
C
        subroutine ranuut (r,s,alpha,beta,x1,x2,lastut,n,buf1,buf2,buf3)
C       implicit none
        integer r, s, alpha, beta, lastut, n
        double precision x1(*), x2(*), buf1(*), buf2(*), buf3(*)
C
C x1 and x2 should be the same in call,
C buf1, buf2 and buf3 should be the same in call (say buf).
C
C Returns n uniformly distributed pseudo-random numbers in
C buf(1..n).
C
C r, s, alpha, beta, x and lastut are as in call to initut.
C
C initut must be called before ranuut to initialize x and lastut.
C It is assumed that x(1..r) and lastut are preserved between calls
C to ranuut.
C
C For comments on the algorithm, see initut and
C CSL Tech. Report TR-CS-92-02.
C
C R. P. Brent, last revised 20011019.
C
        integer del, j, high, low, n2, nr, ns, num, num2, rs, r1, s1
        double precision b, temp, temp2
C Separate routines for alpha .eq. 1 and alpha .ne. 1 so some
C optimisations can be performed.
        if (alpha .ne. 1) then
          call ran2ut (r,s,alpha,beta,x1,x2,lastut,n,buf1,buf2)
          return
          endif
        if (n .le. 0) return
        n2 = n
        rs = r - s
        del = 0
        b = dfloat(beta)
10      num = min (r-lastut, n2)
        n2 = n2 - num
C
C Copy up to r random numbers (previously saved in x) to buf
C
        do 20 j = 1, num
20      buf1(del+j) = x1(lastut+j)
C
        del = del + num
        lastut = lastut + num
        if (lastut .eq. r) then
C
C Following if ... then ... else can be omitted, but reduces
C copying overheads (by working directly in buf) if n > r
C
          if ((del .ge. r) .and. (n2 .gt. 0)) then
C
30          num = min (s, n2)
C Following is the most important loop if n >> r.  The loop is
C unrolled (saving about 0.14 cycles per random number on VP 2200/10).
C Other loops could also be unrolled, but the saving would be
C small for n >> r.
            num2 = num/2
            if (num2 .gt. 0) then
              r1 = r - num2
              s1 = s - num2
C Following loop can safely be vectorised
              do 40 j = del+1, del+num2
              temp  = buf1(j-r)  + b*buf1(j-s)
              temp2 = buf1(j-r1) + b*buf1(j-s1)
              buf2(j)      = temp  - dfloat(int(temp))
40            buf3(j+num2) = temp2 - dfloat(int(temp2))
              endif
C
            del = del + num
            if (2*num2 .lt. num) then
              temp = buf1(del-r) + b*buf1(del-s)
              buf2(del) = temp - dfloat(int(temp))
              endif
C
            n2 = n2 - num
            if (n2 .gt. 0) goto 30
            nr = n - r
            ns = n - s
C
C Now generate r numbers for x(1..r) (avoiding unnecessary copying).
C Following loop can safely be vectorised.
C
            do 50 j = 1, s
            temp = buf1(j+nr) + b*buf1(j+ns)
50          x1(j) = temp - dfloat(int(temp))
C
C Following loop can safely be vectorised.
C No need to split as r - s < s.
C
            do 60 j = s+1, r
            temp = buf1(j+nr) + b*x1(j-s)
60          x2(j) = temp - dfloat(int(temp))
C
          else
C
C Generate another batch of r random numbers.
C Following two loops are equivalent to
C           call fil2ut (r, s, 1, beta, x, x)
C but coded in-line to reduce subroutine call overheads.
C
C Following loop has to be split into segments of size at most rs
C because the use of multiple load/store pipes might otherwise
C give incorrect results.
C
            low = 1
            high = rs
C Following loop can safely be vectorised.
70          do 80 j = low, high
            temp = x1(j) + b*x1(j+rs)
80          x2(j) = temp - dfloat(int(temp))
            low = high + 1
            high = min (s, high + rs)
            if (low .le. high) go to 70
C
C Following loop can safely be vectorised.
            do 90 j = s+1, r
            temp = x1(j) + b*x1(j-s)
90          x2(j) = temp - dfloat(int(temp))
C
            endif
C
          lastut = 0
          endif
        if (n2 .gt. 0) go to 10
        return
        end
C
        subroutine ran2ut (r,s,alpha,beta,x1,x2,lastut,n,buf1,buf2)
C       implicit none
        integer r, s, alpha, beta, lastut, n
        double precision x1(*), x2(*), buf1(*), buf2(*)
C
C x1 and x2 should be the same in call,
C buf1 and buf2 should be the same in call (say buf).
C
C Returns n uniformly distributed pseudo-random numbers in
C buf(1..n).
C
C r, s, alpha, beta, x and lastut are as in call to initut.
C
C initut must be called before ran2ut to initialize x and lastut.
C It is assumed that x(1..r) and lastut are preserved between calls
C to ran2ut.
C
C ran2ut is similar to ranuut except that it is not assumed that
C alpha .eq. 1.
C
C R. P. Brent, last revised 20011019.
C
        integer del, j, high, low, n2, nr, ns, num, rs
        double precision a, b, temp
        if (n .le. 0) return
        n2 = n
        rs = r - s
        del = 0
        a = dfloat(alpha)
        b = dfloat(beta)
10      num = min (r-lastut, n2)
        n2 = n2 - num
C
C Copy up to r random numbers (previously saved in x) to buf
C
        do 20 j = 1, num
20      buf1(del+j) = x1(lastut+j)
C
        del = del + num
        lastut = lastut + num
        if (lastut .eq. r) then
C
C Following if ... then ... else can be omitted, but reduces
C copying overheads (by working directly in buf) if n > r
C
          if ((del .ge. r) .and. (n2 .gt. 0)) then
C
30          num = min (s, n2)
C Following loop can safely be vectorised.
            do 40 j = del+1, del+num
            temp = a*buf1(j-r) + b*buf1(j-s)
40          buf2(j) = temp - dfloat(int(temp))
C
            del = del + num
            n2 = n2 - num
            if (n2 .gt. 0) goto 30
            nr = n - r
            ns = n - s
C
C Now generate r numbers for x(1..r) (avoiding unnecessary copying).
C Following loop can safely be vectorised.
C
            do 50 j = 1, s
            temp = a*buf1(j+nr) + b*buf1(j+ns)
50          x1(j) = temp - dfloat(int(temp))
C
C Following loop can safely be vectorised.
C No need to split as r - s < s.
C
            do 60 j = s+1, r
            temp = a*buf1(j+nr) + b*x1(j-s)
60          x2(j) = temp - dfloat(int(temp))
C
          else
C
C Generate another batch of r random numbers.
C Following two loops are equivalent to
C           call fil2ut (r, s, alpha, beta, x, x)
C but coded in-line to reduce subroutine call overheads.
C
C Following loop has to be split into segments of size at most rs.
C
            low = 1
            high = rs
C Following loop can safely be vectorised.
65          do 70 j = low, high
            temp = a*x1(j) + b*x1(j+rs)
70          x2(j) = temp - dfloat(int(temp))
            low = high + 1
            high = min (s, high + rs)
            if (low .le. high) go to 65
C
C Following loop can safely be vectorised.
            do 80 j = s+1, r
            temp = a*x1(j) + b*x1(j-s)
80          x2(j) = temp - dfloat(int(temp))
C
            endif
C
          lastut = 0
          endif
        if (n2 .gt. 0) go to 10
        return
        end
C
        subroutine fil2ut (r, s, alpha, beta, x1, x2)
C       implicit none
        integer r, s, alpha, beta
        double precision x1(*), x2(*)
C
C This routine should be called by with x1, x2 the same array (say x).
C This makes the compiler generate faster code (but we have to
C be careful about serialization).
C
C Generates r more random numbers to replace those already in
C the array x(1..r).  r must be as in the call to initut,
C and x(1..r) must be preserved between calls.
C
C Uses a generalized Fibonacci recurrence
C x(n) = alpha*x(n-r) + beta*x(n-s) mod 1,
C where 0 < s < r < 2s,
C x^r + x^s + 1 is primitive (mod 2) (see comments in initut)
C alpha and beta are small odd positive integers,
C (to avoid losing more than 4 bits, alpha + beta <= 16 recommended),
C and operations are performed exactly on floating-point
C numbers mod 2^nw (but scaled by 2^(-nw) so result in range [0,1]).
C
C NB: initut must be called before fil2ut is called.
C
C R. P. Brent, last revised 20011019.
C
        double precision a, b, t1
        integer j, rs, low, high
        rs = r - s
        b = dfloat(beta)
        a = dfloat(alpha)
        low = 1
        high = rs
C
C Following two inner loops vectorize safely since 0 < r-s < s.
C First loop over j = 1..s is split into pieces of size at most r-s.
C Not worth expanding loops except in case alpha = 1 (see fil3ut).
C
C NB: Because we use x1, x2 with same address, it is important
C     that high - low < rs (otherwise use of multiple load/store
C     pipes might give incorrect results).
C
C Following loop can safely be vectorised.
10      do 20 j = low, high
        t1 = a*x1(j) + b*x1(j+rs)
20      x2(j) = t1 - dfloat(int(t1))
        low = high + 1
        high = min (s, high + rs)
        if (low .le. high) go to 10
C
C Following loop can safely be vectorised.
C We assume r - s < s.
C
        do 30 j = s+1, r
        t1 = a*x1(j) + b*x1(j-s)
30      x2(j) = t1 - dfloat(int(t1))
        return
        end
C
        subroutine skiput (r, s, n, p2, x, xb, eps)
C       implicit none
        integer r, s, n, p2
        double precision x(*), xb(*), eps
C
C Initializes x(1..r) so that last bits of subsequent sequence
C start at index 1 + n*2^p2 instead of 1.
C n and p2 should be non-negative.
C eps is one unit in last bit position (i.e. 2^(-nw)).
C xb is a work array of dimension at least 2*r.
C
C R. P. Brent, last revised 20011019.
C
        integer j, n2, nrev, ns, rs
        rs = r - s
C Initialize xb to (-1, 1, 1, ... 1) where -1 means true, 1 means false
C so multiplication simulates xor.
C (xb could be an array of characters or bits - double precision is
C used for historical reasons and because the operations vectorise
C on certain machines.)
        xb(1) = -1.0d0
        do 10 j = 2, 2*r
10      xb(j) = 1.0d0
C Extract bits in binary representation of n
C and store in nrev (i.e. nrev <- n with bits reversed).
        n2 = max (n, 0)
        ns = 0
        nrev = 0
        if (n2 .gt. 0) then
20        ns = ns + 1
          nrev = 2*nrev + mod(n2,2)
          n2 = n2/2
          if (n2 .gt. 0) goto 20
C Raise polynomial to n-th power using reversed bit representation
          do 30 j = 1, ns
          call sqshut (r, s, .true., (mod(nrev,2) .eq. 1), xb, xb, xb)
30        nrev = nrev/2
          endif
C Square polynomial p2 times
        if (p2 .gt. 0) then
          do 40 j = 1, p2
40        call sqshut (r, s, .true., .false., xb, xb, xb)
          endif
C Set last bits of x[1..rb]
C Could call sqshut r times, but following loops are more efficient.
        do 50 j = 1, r
50      x(j) = 0.0d0
        if (xb(1) .lt. 0d0) x(1) = eps
C Following loop can safely be vectorised.
        do 60 j = 0, rs-1
        if (xb(r-j) .lt. 0d0) then
          xb(rs-j) = -xb(rs-j)
          x(j+2) = eps
          endif
60      continue
C Following loop can safely be vectorised.
        do 70 j = rs, r-2
        if (xb(r-j) .lt. 0d0) x(j+2) = eps
70      continue
        return
        end
C
        subroutine sqshut (r, s, square, shiftr, xb1, xb2, xb3)
        integer r, s
        logical square, shiftr
        double precision xb1(*), xb2(*), xb3(*)
C
C NB: xb1, xb2 and xb3 should be identical (say xb) in call.
C
C Reduces polynomial (mod 2) defined by xb(1..r)
C modulo Q(t) = t^r + t^(r-s) + 1 (reverse of generating polynomial)
C
C Input  P(t) <- xb(1) + xb(2)*t + ... + xb(r)*t^(r-1).
C Define P'(t) = P(t)*P(t) if square, P(t) otherwise,
C        P"(t) = t*P'(t)   if shiftr, P'(t) otherwise.
C Output is P"(t) mod Q(t) -> xb(1) + xb(2)*t + ... + xb(r)*t^(r-1)
C
C R. P. Brent, last revised 20011009.
C
        integer j, rh
        if (square) then
          rh = 2*r
C Square input polynomial (mod 2) - note that cross terms vanish
          do 10 j = r, 1, -1
          xb1(2*j) = 1.0d0
10        xb1(2*j-1) = xb1(j)
        else
          rh = r+1
          endif
C Right shift if necessary
        if (shiftr) then
          do 20 j = rh, 2, -1
20        xb1(j) = xb1(j-1)
          xb1(1) = 1.0d0
          endif
C Reduction mod Q
        if (rh .eq. 2*r) then
C Split up loop into pieces of size at most s so will vectorize
C Warning - do not try to combine next two loops !
C Following loop can safely be vectorised.
          do 30 j = rh+1-s, rh
30        xb1(j-s) = xb2(j)*xb1(j-s)
C Following loop can safely be vectorised.
          do 40 j = rh+1-s, rh
          xb1(j-r) = xb2(j)*xb1(j-r)
40        xb2(j)   = 1.0d0
C Following loop can safely be vectorised.
          do 50 j = r+1, rh-s
          xb1(j-s) = xb2(j)*xb1(j-s)
          xb3(j-r) = xb2(j)*xb3(j-r)
50        xb2(j)   = 1.0d0
        else
C Here rh = r+1 so no need for loop
          if (xb1(rh) .lt. 0d0) then
            xb1(rh)   = 1.0d0
            xb1(rh-s) = -xb1(rh-s)
            xb1(rh-r) = -xb1(rh-r)
            endif
          endif
        return
        end
C
C End of ranut.f and associated routines
C =====================================================================
