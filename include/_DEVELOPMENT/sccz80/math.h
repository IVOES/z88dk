
// automatically generated by m4 from headers in proto subdir


#ifndef __MATH_H__
#define __MATH_H__

// THE SELECTED FLOATING POINT PACKAGE MAY NOT SUPPORT ALL LISTED FUNCTIONS

#ifndef _FLOAT_T_DEFINED
#define _FLOAT_T_DEFINED

   #ifdef __CLANG
   
   typedef float float_t;
   
   #endif

   #ifdef __SDCC
   
   typedef float float_t;
   
   #endif
   
   #ifdef __SCCZ80
   
   typedef double float_t;
   
   #endif
   
#endif

#ifndef _DOUBLE_T_DEFINED
#define _DOUBLE_T_DEFINED

   #ifdef __CLANG
   
   typedef float double_t;
   
   #endif

   #ifdef __SDCC
   
   typedef float double_t;
   
   #endif
   
   #ifdef __SCCZ80
   
   typedef double double_t;
   
   #endif
   
#endif

// XSI EXTENSION
// temporary : math lib should supply these via func call

#define M_E                    2.718281828459
#define M_LOG2E                1.442695040889
#define M_LOG10E               0.4342944819033
#define M_LN2                  0.693147180560
#define M_LN10                 2.302585092994
#define M_PI                   3.141592653590
#define M_PI_2                 1.570796326795
#define M_PI_4                 0.7853981633974
#define M_1_PI                 0.3183098861838
#define M_2_PI                 0.6366197723676
#define M_2_SQRTPI             1.128379167096
#define M_SQRT2                1.414213562373
#define M_SQRT1_2              0.7071067811865

//

#define FLT_EVAL_METHOD        1
#define MATH_ERRNO             1
#define MATH_ERREXCEPT         2
#define math_errhandling       1

#ifdef __CLANG

#define HUGE_VAL               1.7014117331E+38
#define HUGE_VALF              1.7014117331E+38
#define INFINITY               1.7014117331E+38

#endif

#ifdef __SDCC

#define HUGE_VAL               1.7014117331E+38
#define HUGE_VALF              1.7014117331E+38
#define INFINITY               1.7014117331E+38

#endif

#ifdef __SCCZ80

#define HUGE_VAL               1.7014118346E+38
#define HUGE_VALF              1.7014118346E+38
#define INFINITY               1.7014118346E+38

#endif

#ifdef __MATH_MATH32

#define HUGE_POSF              (float)+3.4028234664E+38
#define TINY_POSF              (float)+1.1754943508E−38
#define HUGE_NEGF              (float)-1.7014118346E+38
#define TINY_NEGF              (float)-1.1754943508E-38

#define MAXL2F                 ((float)+127.999999914)
#define MINL2F                 ((float)-126.0)
#define MAXL10F                ((float)+38.230809449)
#define MINL10F                ((float)−37.929779454)

#endif

extern double_t __LIB__ acos(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ asin(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ atan(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ atan2(double_t y,double_t x) __smallc;
extern double_t __LIB__ atan2_callee(double_t y,double_t x) __smallc __z88dk_callee;
#define atan2(a,b) atan2_callee(a,b)



extern double_t __LIB__ cos(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ sin(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ tan(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ acosh(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ asinh(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ atanh(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ cosh(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ sinh(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ tanh(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ exp(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ exp2(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ expm1(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ frexp(double_t value,int *exp) __smallc;
extern double_t __LIB__ frexp_callee(double_t value,int *exp) __smallc __z88dk_callee;
#define frexp(a,b) frexp_callee(a,b)


extern int __LIB__ ilogb(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ ldexp(double_t x,int exp) __smallc;
extern double_t __LIB__ ldexp_callee(double_t x,int exp) __smallc __z88dk_callee;
#define ldexp(a,b) ldexp_callee(a,b)



extern double_t __LIB__ log(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ log10(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ log1p(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ log2(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ logb(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ scalbn(double_t x,int n) __smallc;
extern double_t __LIB__ scalbn_callee(double_t x,int n) __smallc __z88dk_callee;
#define scalbn(a,b) scalbn_callee(a,b)


extern double_t __LIB__ scalbln(double_t x,int n) __smallc;
extern double_t __LIB__ scalbln_callee(double_t x,int n) __smallc __z88dk_callee;
#define scalbln(a,b) scalbln_callee(a,b)



extern double_t __LIB__ fabs(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ hypot(double_t x,double_t y) __smallc;
extern double_t __LIB__ hypot_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define hypot(a,b) hypot_callee(a,b)



extern double_t __LIB__ pow(double_t x,double_t y) __smallc;
extern double_t __LIB__ pow_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define pow(a,b) pow_callee(a,b)


extern double_t __LIB__ sqrt(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ cbrt(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ erf(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ erfc(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ lgamma(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ tgamma(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ ceil(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ floor(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ nearbyint(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ rint(double_t x) __smallc __z88dk_fastcall;


extern long __LIB__ lrint(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ round(double_t x) __smallc __z88dk_fastcall;


extern long __LIB__ lround(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ trunc(double_t x) __smallc __z88dk_fastcall;



extern double_t __LIB__ modf(double_t value,double_t *iptr) __smallc;
extern double_t __LIB__ modf_callee(double_t value,double_t *iptr) __smallc __z88dk_callee;
#define modf(a,b) modf_callee(a,b)


extern double_t __LIB__ fmod(double_t x,double_t y) __smallc;
extern double_t __LIB__ fmod_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define fmod(a,b) fmod_callee(a,b)


extern double_t __LIB__ remainder(double_t x,double_t y) __smallc;
extern double_t __LIB__ remainder_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define remainder(a,b) remainder_callee(a,b)


extern double_t __LIB__ remquo(double_t x,double_t y,int *quo) __smallc;
extern double_t __LIB__ remquo_callee(double_t x,double_t y,int *quo) __smallc __z88dk_callee;
#define remquo(a,b,c) remquo_callee(a,b,c)



extern double_t __LIB__ copysign(double_t x,double_t y) __smallc;
extern double_t __LIB__ copysign_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define copysign(a,b) copysign_callee(a,b)


extern double_t __LIB__ nan(const char *tagp) __smallc __z88dk_fastcall;



extern double_t __LIB__ nextafter(double_t x,double_t y) __smallc;
extern double_t __LIB__ nextafter_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define nextafter(a,b) nextafter_callee(a,b)


extern double_t __LIB__ nexttoward(double_t x,double_t y) __smallc;
extern double_t __LIB__ nexttoward_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define nexttoward(a,b) nexttoward_callee(a,b)



extern double_t __LIB__ fdim(double_t x,double_t y) __smallc;
extern double_t __LIB__ fdim_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define fdim(a,b) fdim_callee(a,b)



extern double_t __LIB__ fmax(double_t x,double_t y) __smallc;
extern double_t __LIB__ fmax_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define fmax(a,b) fmax_callee(a,b)


extern double_t __LIB__ fmin(double_t x,double_t y) __smallc;
extern double_t __LIB__ fmin_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define fmin(a,b) fmin_callee(a,b)



extern double_t __LIB__ fma(double_t x,double_t y,double_t z) __smallc;
extern double_t __LIB__ fma_callee(double_t x,double_t y,double_t z) __smallc __z88dk_callee;
#define fma(a,b,c) fma_callee(a,b,c)



extern int __LIB__ isgreater(double_t x,double_t y) __smallc;
extern int __LIB__ isgreater_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define isgreater(a,b) isgreater_callee(a,b)


extern int __LIB__ isgreaterequal(double_t x,double_t y) __smallc;
extern int __LIB__ isgreaterequal_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define isgreaterequal(a,b) isgreaterequal_callee(a,b)


extern int __LIB__ isless(double_t x,double_t y) __smallc;
extern int __LIB__ isless_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define isless(a,b) isless_callee(a,b)


extern int __LIB__ islessequal(double_t x,double_t y) __smallc;
extern int __LIB__ islessequal_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define islessequal(a,b) islessequal_callee(a,b)


extern int __LIB__ islessgreater(double_t x,double_t y) __smallc;
extern int __LIB__ islessgreater_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define islessgreater(a,b) islessgreater_callee(a,b)


extern int __LIB__ isunordered(double_t x,double_t y) __smallc;
extern int __LIB__ isunordered_callee(double_t x,double_t y) __smallc __z88dk_callee;
#define isunordered(a,b) isunordered_callee(a,b)



#ifdef __MATH_MATH32

extern double_t __LIB__ sqr(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ inv(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ invsqrt(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ div2(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ mul2(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ mul10u(double_t x) __smallc __z88dk_fastcall;


extern double_t __LIB__ exp10(double_t x) __smallc __z88dk_fastcall;



#endif

// NO DISTINCTION BETWEEN FLOAT AND DOUBLE

#define acosf        acos
#define asinf        asin
#define atanf        atan
#define atan2f       atan2

#define cosf         cos
#define sinf         sin
#define tanf         tan

#define acoshf       acosh
#define asinhf       asinh
#define atanhf       atanh

#define coshf        cosh
#define sinhf        sinh
#define tanhf        tanh

#define expf         exp
#define exp2f        exp2
#define expm1f       expm1
#define frexpf       frexp
#define ilogbf       ilogb
#define ldexpf       ldexp

#define logf         log
#define log10f       log10
#define log1pf       log1p
#define log2f        log2
#define logbf        logb

#define scalbnf      scalbn
#define scalblnf     scalbln

#define fabsf        fabs
#define hypotf       hypot

#define powf         pow
#define sqrtf        sqrt
#define cbrtf        cbrt

#define erff         erf
#define erfcf        erfc
#define lgammaf      lgamma
#define tgammaf      tgamma

#define ceilf        ceil
#define floorf       floor
#define nearbyintf   nearbyint
#define rintf        rint
#define lrintf       lrint
#define llrintf      llrint
#define roundf       round
#define lroundf      lround
#define llroundf     llround
#define truncf       trunc

#define modff        modf
#define fmodf        fmod
#define remainderf   remainder
#define remquof      remquo

#define copysignf    copysign
#define nanf         nan

#define nextafterf   nextafter
#define nexttowardf  nexttoward

#define fdimf        fdim

#define fmaxf        fmax
#define fminf        fmin

#define fmaf         fma

#ifdef __MATH_MATH32

#define sqrf         sqr
#define invf         inv
#define invsqrtf     insqrt
#define div2f        div2
#define mul2f        mul2
#define mul10uf      mul10u
#define exp10f       exp10

#endif

#endif
