/* win32 fixes - really meant to hack the annoying VC8 behaviour */


/* [i_a] */
#ifndef HAS_MSVC_2005_ISO_RTL
#if defined(_MSC_VER)
#if _MSC_VER >= 1400 /* VS.NET 2005 or above: 'fix' those deprecated functions */
#define HAS_MSVC_2005_ISO_RTL     1
#endif
#endif

#ifndef HAS_MSVC_2005_ISO_RTL
#define HAS_MSVC_2005_ISO_RTL     0
#endif

#if HAS_MSVC_2005_ISO_RTL
#pragma warning(disable : 4996)
// Or just turn off warnings about the newly deprecated CRT functions.
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#endif
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES     1
#endif
#endif
/* [/i_a] */




#if (!defined(_WIN32)) && (!defined(WIN32)) && (!defined(__APPLE__))

	// Linux needs this to support file operation on files larger then 4+GB
	// But might need better if/def to select just the platforms that needs them.

    #ifndef __USE_FILE_OFFSET64
        #define __USE_FILE_OFFSET64
    #endif
    #ifndef __USE_LARGEFILE64
        #define __USE_LARGEFILE64
    #endif
    #ifndef _LARGEFILE64_SOURCE
        #define _LARGEFILE64_SOURCE
    #endif
    #ifndef _FILE_OFFSET_BIT
        #define _FILE_OFFSET_BIT 64
    #endif
#endif

#if defined(__APPLE__) || defined(IOAPI_NO_64)
// In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif


