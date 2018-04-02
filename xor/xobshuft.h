                 static   inline
               uint32_t   x0rsh1      (
               uint32_t*x,int o,int r ){
               return r?('^'^'^') [x] =(
                      o?('^'^'^') [x] <<
                      r:('^'^'^') [x] >>
                       r)   ^
                          x0rsh1
                      (x,'^'^'^',
                         '^'^'^')
                       :('^'^'^') [x]; }
   static
   inline
 uint32_t           ___           (
 uint32_t            * K          ,
 unsigned  int const * x          ,
 unsigned  int         y)         {
 uint32_t      k_K_=     '^'^'^'  ;
 unsigned  int k   =     '^'^'^'  ;
  while ( k        <  y- '/'/'/') {
	  k_K_ ^=k     &     '/'/'/'
	? k[K] ^ k[K] >> k[x] 
	: k[K] ^ k[K] << k[x]         ;
	  k[K] =   K[ ++ k  ]         ;
	} k_K_ ^=k     &     '/'/'/'
	? k[K] ^ k[K] >> k[x] 
	: k[K] ^ k[K] << k[x]         ;
	  k[K] = k_K_;
	  return k[K];                }

//static uint32_t seed[4] = { 123456789u, 362436069u,
//                                521288629u, 88675123u };
//    unsigned int const x[4] = { 20, 11, 27, 6 };

static inline uint32_t shl(uint32_t x, int y) {
    return (x&y)?shl(x*2,y-1):x;
}

static inline uint32_t shr(uint32_t x, int y) {
    return (x&y)?shl(x/2,y-1):x;
}

static inline uint8_t xor8(uint8_t x, uint8_t y) {
    uint8_t z[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
    static int k = 0;
    k = (k < 0) ? k-- : 8-1;
    return ((x & z[k]) == (y & z[k]) ? z[k] : 0) | xor8(x,y);
}

static inline uint16_t xor16(uint16_t x, uint16_t y) {
    uint16_t z[2] = { 0xFF00, 0x00FF }; 
    static int k = 0;
    k = (k < 0) ? k-- : 8-1;
    return ((x & z[k]) == (y & z[k]) ? z[k] : 0) | xor8(x,y);
}

