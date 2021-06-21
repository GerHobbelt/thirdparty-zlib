/* Generated by fuzzing - test bi_valid handling in deflate_quick(). */

#include "zbuild.h"
#ifdef ZLIB_COMPAT
#  include "zlib.h"
#else
#  include "zlib-ng.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(BUILD_MONOLITHIC)
#define main()      zlib_deflate_quick_bi_valid_test_main()
#endif

int main()
{
    PREFIX3(stream) strm;
    memset(&strm, 0, sizeof(strm));

    int ret = PREFIX(deflateInit2)(&strm, 1, Z_DEFLATED, 31, 1, Z_FILTERED);
    if (ret != Z_OK) {
        fprintf(stderr, "deflateInit2() failed with code %d\n", ret);
        return EXIT_FAILURE;
    }

    z_const unsigned char next_in[554] =
            "\x8d\xff\xff\xff\xa2\x00\x00\xff\x00\x15\x1b\x1b\xa2\xa2\xaf\xa2"
            "\xa2\x00\x00\x00\x02\x00\x1b\x3f\x00\x00\x01\x00\x00\x00\x00\x0b"
            "\x00\xab\x00\x00\x00\x00\x01\x00\x01\x2b\x01\x00\x00\x00\x00\x00"
            "\x00\x01\x1e\x00\x00\x01\x40\x00\x00\x00\x07\x01\x18\x00\x22\x00"
            "\x00\x00\xfd\x39\xff\x00\x00\x00\x1b\xfd\x3b\x00\x68\x00\x00\x01"
            "\xff\xff\xff\x57\xf8\x1e\x00\x00\xf2\xf2\xf2\xf2\xfa\xff\xff\xff"
            "\xff\x7e\x00\x00\x4a\x00\xc5\x00\x41\x00\x00\x00\x01\x01\x00\x00"
            "\x00\x02\x01\x01\x00\xa2\x08\x00\x00\x00\x00\x27\x4a\x4a\x4a\x32"
            "\x00\xf9\xff\x00\x02\x9a\xff\x00\x00\x3f\x50\x00\x03\x00\x00\x00"
            "\x3d\x00\x08\x2f\x20\x00\x23\x00\x00\x00\x00\x23\x00\xff\xff\xff"
            "\xff\xff\xff\xff\x7a\x7a\x9e\xff\xff\x00\x1b\x1b\x04\x00\x1b\x1b"
            "\x1b\x1b\x00\x00\x00\xaf\xad\xaf\x00\x00\xa8\x00\x00\x00\x2e\xff"
            "\xff\x2e\xc1\x00\x10\x00\x00\x00\x06\x70\x00\x00\x00\xda\x67\x01"
            "\x47\x00\x00\x00\x0c\x02\x00\x00\x00\x00\x00\xff\x00\x01\x00\x3f"
            "\x54\x00\x00\x00\x1b\x00\x00\x00\x5c\x00\x00\x34\x3e\xc5\x00\x00"
            "\x00\x00\x00\x04\x00\x00\x7a\x00\x00\x00\x0a\x01\x00\x00\x00\x00"
            "\x00\x00\x7a\x7a\x7a\x7a\x7a\x00\x00\x00\x40\x1b\x1b\x88\x1b\x1b"
            "\x1b\x1b\x1b\x1b\x1b\x1f\x1b\x00\x00\x00\x00\x00\x0b\x00\x00\x00"
            "\x00\x04\x00\x00\x50\x3e\x7a\x7a\x00\x00\x40\x00\x40\x00\x00\x00"
            "\x00\x00\x00\x08\x87\x00\x00\xff\xff\xff\x00\x00\x00\x00\x00\x00"
            "\x01\x00\xff\x3d\x00\x11\x4d\x00\x00\x01\xd4\xd4\xd4\xd4\x2d\xd4"
            "\xd4\xff\xff\xff\xfa\x01\xd4\x00\xd4\x00\x00\xd4\xd4\xd4\xd4\xd4"
            "\xd4\x1e\x1e\x1e\x1e\x00\x00\xfe\xf9\x1e\x1e\x1e\x1e\x1e\x1e\x00"
            "\x16\xd4\xd4\xd4\xd4\xd4\xd4\xd4\xd4\xd4\x00\x00\x80\x20\x00\x00"
            "\xff\x2b\x2b\x2b\x2b\x35\xd4\xd4\x47\x3f\xd4\xd4\xd6\xd4\xd4\x00"
            "\x00\x00\x00\x00\x32\x4a\x4a\x4a\x4a\x71\x00\x1b\x1b\x1b\x1b\x1b"
            "\x1f\x1b\x1b\x1b\x57\x57\x57\x57\x00\x00\x1b\x08\x2b\x16\xc3\x00"
            "\x00\x00\x29\x30\x03\xff\x03\x03\x03\x03\x07\x00\x00\x01\x0b\xff"
            "\xff\xf5\xf5\xf5\x00\x00\xfe\xfa\x0f\x0f\x08\x00\xff\x00\x53\x3f"
            "\x00\x04\x5d\xa8\x2e\xff\xff\x00\x2f\x2f\x05\xff\xff\xff\x2f\x2f"
            "\x2f\x0a\x0a\x0a\x0a\x30\xff\xff\xff\xf0\x0a\x0a\x0a\x00\xff\x3f"
            "\x4f\x00\x00\x00\x00\x08\x00\x00\x71\x00\x2e\x00\x00\x00\x00\x00"
            "\x71\x71\x00\x71\x71\x71\xf5\x00\x00\x00\x00\x00\x00\x00\xf8\xff"
            "\xff\xff\x00\x00\x00\x00\x00\xdb\x3f\x00\xfa\x71\x71\x71\x00\x00"
            "\x00\x01\x00\x00\x00\x71\x71\x71\x71\x71";
    strm.next_in = next_in;
    unsigned char next_out[1236];
    strm.next_out = next_out;

    strm.avail_in = 554;
    strm.avail_out = 31;
    ret = PREFIX(deflate)(&strm, Z_FINISH);
    if (ret != Z_OK) {
        fprintf(stderr, "deflate() failed with code %d\n", ret);
        return EXIT_FAILURE;
    }

    strm.avail_in = 0;
    strm.avail_out = 498;
    ret = PREFIX(deflate)(&strm, Z_FINISH);
    if (ret != Z_STREAM_END) {
        fprintf(stderr, "deflate() failed with code %d\n", ret);
        return EXIT_FAILURE;
    }

    ret = PREFIX(deflateEnd)(&strm);
    if (ret != Z_OK) {
        fprintf(stderr, "deflateEnd() failed with code %d\n", ret);
        return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
