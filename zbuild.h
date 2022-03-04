#ifndef _ZBUILD_H
#define _ZBUILD_H

#define _POSIX_SOURCE 1  /* fileno */
#ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200112L /* snprintf, posix_memalign */
#endif

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* Determine compiler version of C Standard */
#ifdef __STDC_VERSION__
#  if __STDC_VERSION__ >= 199901L
#    ifndef STDC99
#      define STDC99
#    endif
#  endif
#  if __STDC_VERSION__ >= 201112L
#    ifndef STDC11
#      define STDC11
#    endif
#  endif
#endif

/* Determine compiler support for TLS */
#ifndef Z_TLS
#  if (defined(STDC11) || (__STDC_VERSION__ >= 201112)) && !defined(__STDC_NO_THREADS__)
#    define Z_TLS _Thread_local
#  elif defined(__GNUC__) || defined(__SUNPRO_C)
#    define Z_TLS __thread
#  elif defined(_WIN32) && (defined(_MSC_VER) || defined(__ICL))
#    define Z_TLS __declspec(thread)
#  else
#    warning Unable to detect Thread Local Storage support.
#    define Z_TLS
#  endif
#endif

/* This has to be first include that defines any types */
#if defined(_MSC_VER)
#if !defined(_SSIZE_T_DEFINED)
#  if defined(_WIN64)
    typedef __int64 ssize_t;
#  else
    typedef long ssize_t;
#  endif
#define _SSIZE_T_DEFINED
#endif

# define __attribute__(x)	/**/
#endif

/* MS Visual Studio does not allow inline in C, only C++.
   But it provides __inline instead, so use that. */
#if defined(_MSC_VER) && !defined(inline) && !defined(__cplusplus)
#  define inline __inline
#endif

#if defined(ZLIB_COMPAT)
#  define PREFIX(x) x
#  define PREFIX2(x) ZLIB_ ## x
#  define PREFIX3(x) z_ ## x
#  define PREFIX4(x) x ## 64
#  define zVersion zlibVersion
#  define z_size_t unsigned long
#else
#  define PREFIX(x) zng_ ## x
#  define PREFIX2(x) ZLIBNG_ ## x
#  define PREFIX3(x) zng_ ## x
#  define PREFIX4(x) zng_ ## x
#  define zVersion zlibng_version
#  define z_size_t size_t
#endif

/* Minimum of a and b. */
#ifndef MIN
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#endif
/* Maximum of a and b. */
#ifndef MAX
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif
/* Ignore unused variable warning */
#define Z_UNUSED(var) (void)(var)

#ifndef Z_INTERNAL
#if defined(HAVE_VISIBILITY_INTERNAL)
#  define Z_INTERNAL __attribute__((visibility ("internal")))
#elif defined(HAVE_VISIBILITY_HIDDEN)
#  define Z_INTERNAL __attribute__((visibility ("hidden")))
#else
#  define Z_INTERNAL
#endif
#endif

#ifndef __cplusplus
#  define Z_REGISTER register
#else
#  define Z_REGISTER
#endif

/* Reverse the bytes in a value. Use compiler intrinsics when
   possible to take advantage of hardware implementations. */
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#  include <stdlib.h>
#  pragma intrinsic(_byteswap_ulong)
#  define ZSWAP16(q) _byteswap_ushort(q)
#  define ZSWAP32(q) _byteswap_ulong(q)
#  define ZSWAP64(q) _byteswap_uint64(q)

#elif defined(__Clang__) || (defined(__GNUC__) && \
        (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)))
#  define ZSWAP16(q) __builtin_bswap16(q)
#  define ZSWAP32(q) __builtin_bswap32(q)
#  define ZSWAP64(q) __builtin_bswap64(q)

#elif defined(__GNUC__) && (__GNUC__ >= 2) && defined(__linux__)
#  include <byteswap.h>
#  define ZSWAP16(q) bswap_16(q)
#  define ZSWAP32(q) bswap_32(q)
#  define ZSWAP64(q) bswap_64(q)

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#  include <sys/endian.h>
#  define ZSWAP16(q) bswap16(q)
#  define ZSWAP32(q) bswap32(q)
#  define ZSWAP64(q) bswap64(q)
#elif defined(__OpenBSD__)
#  include <sys/endian.h>
#  define ZSWAP16(q) swap16(q)
#  define ZSWAP32(q) swap32(q)
#  define ZSWAP64(q) swap64(q)
#elif defined(__INTEL_COMPILER)
/* ICC does not provide a two byte swap. */
#  define ZSWAP16(q) ((((q) & 0xff) << 8) | (((q) & 0xff00) >> 8))
#  define ZSWAP32(q) _bswap(q)
#  define ZSWAP64(q) _bswap64(q)

#else
#  define ZSWAP16(q) ((((q) & 0xff) << 8) | (((q) & 0xff00) >> 8))
#  define ZSWAP32(q) ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + \
                     (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))
#  define ZSWAP64(q)                           \
         (((q & 0xFF00000000000000u) >> 56u) | \
          ((q & 0x00FF000000000000u) >> 40u) | \
          ((q & 0x0000FF0000000000u) >> 24u) | \
          ((q & 0x000000FF00000000u) >> 8u)  | \
          ((q & 0x00000000FF000000u) << 8u)  | \
          ((q & 0x0000000000FF0000u) << 24u) | \
          ((q & 0x000000000000FF00u) << 40u) | \
          ((q & 0x00000000000000FFu) << 56u))
#endif

/* nuke any previous definitions which may clash with the subsequent ones. This can happen when other libraries re-use this header file. */
#undef LIKELY_NULL
#undef LIKELY
#undef UNLIKELY
#undef PREFETCH_L1
#undef PREFETCH_L2
#undef PREFETCH_RW

/* Only enable likely/unlikely if the compiler is known to support it */
#if (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__INTEL_COMPILER) || defined(__Clang__)
#  define LIKELY_NULL(x)        __builtin_expect((x) != 0, 0)
#  define LIKELY(x)             __builtin_expect(!!(x), 1)
#  define UNLIKELY(x)           __builtin_expect(!!(x), 0)
#  define PREFETCH_L1(addr)     __builtin_prefetch(addr, 0, 3)
#  define PREFETCH_L2(addr)     __builtin_prefetch(addr, 0, 2)
#  define PREFETCH_RW(addr)     __builtin_prefetch(addr, 1, 2)
#elif defined(__WIN__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86_FP))  /* _mm_prefetch() is not defined outside of x86/x64 */ )
#  include <mmintrin.h>   /* https://docs.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170 */

#if defined(__SSE__) || (_M_IX86_FP >= 1)
#  include <xmmintrin.h>
#endif
#if defined(__SSE2__) || (_M_IX86_FP >= 2)
#  include <emmintrin.h>
#endif

#if defined(__SSE2__) || (_M_IX86_FP >= 2)
#  include <pmmintrin.h>     //SSE3
#  include <tmmintrin.h>     //SSSE3
#endif

#if defined(__AVX__) || (_M_IX86_FP >= 2)
#  include <immintrin.h>
#endif

#  define LIKELY_NULL(x)        (x)
#  define LIKELY(x)             (x)
#  define UNLIKELY(x)           (x)
#  define PREFETCH_L1(addr)     _mm_prefetch((char *) (addr), _MM_HINT_T0)
#  define PREFETCH_L2(addr)     _mm_prefetch((char *) (addr), _MM_HINT_T1)
#  define PREFETCH_RW(addr)     _mm_prefetch((char *) (addr), _MM_HINT_T1)
#elif defined(__aarch64__)
#  define LIKELY_NULL(x)        (x)
#  define LIKELY(x)             (x)
#  define UNLIKELY(x)           (x)
#  define PREFETCH_L1(ptr)  __asm__ __volatile__("prfm pldl1keep, %0" ::"Q"(*(ptr)))
#  define PREFETCH_L2(ptr)  __asm__ __volatile__("prfm pldl2keep, %0" ::"Q"(*(ptr)))
#  define PREFETCH_RW(addr)     (addr)
#else
#  define LIKELY_NULL(x)        (x)
#  define LIKELY(x)             (x)
#  define UNLIKELY(x)           (x)
#  define PREFETCH_L1(addr)     (addr)
#  define PREFETCH_L2(addr)     (addr)
#  define PREFETCH_RW(addr)     (addr)
#endif /* (un)likely */

#if defined(__clang__) || defined(__GNUC__)
#  define ALIGNED_(x) __attribute__ ((aligned(x)))
#elif defined(_MSC_VER)
#  define ALIGNED_(x) __declspec(align(x))
#endif

/* Diagnostic functions */
#ifdef ZLIB_DEBUG
#  include <stdio.h>
   extern int Z_INTERNAL z_verbose;
   extern void Z_INTERNAL z_error(char *m);
#  define Assert(cond, msg) {if (!(cond)) z_error(msg);}
#  define Trace(x) {if (z_verbose >= 0) fprintf x;}
#  define Tracev(x) {if (z_verbose > 0) fprintf x;}
#  define Tracevv(x) {if (z_verbose > 1) fprintf x;}
#  define Tracec(c, x) {if (z_verbose > 0 && (c)) fprintf x;}
#  define Tracecv(c, x) {if (z_verbose > 1 && (c)) fprintf x;}
#else
#  define Assert(cond, msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c, x)
#  define Tracecv(c, x)
#endif

#endif
