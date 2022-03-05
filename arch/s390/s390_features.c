#if !defined(_MSC_VER)

#include "../../zbuild.h"
#include "../../zutil.h"
#include "s390_features.h"

#include <sys/auxv.h>

Z_INTERNAL int s390_cpu_has_vx;

void Z_INTERNAL s390_check_features(void) {
    s390_cpu_has_vx = getauxval(AT_HWCAP) & HWCAP_S390_VX;
}

#endif
