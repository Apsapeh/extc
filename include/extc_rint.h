/* Define Rust-like type names */

typedef char  i8;
typedef short i16;
typedef int   i32;
typedef long  isize;
#if (__STDC_VERSION__ >= 199901L)
    typedef long long i64;
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  usize;
#if (__STDC_VERSION__ >= 199901L)
    typedef unsigned long long u64;
#endif

typedef float f32;
typedef double f64;

#define true  1
#define false 0

#define and &&
#define or  ||
#define not !
