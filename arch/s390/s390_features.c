#if !defined(_MSC_VER)

#include "../../zbuild.h"
#include "../../zutil.h"
#include "s390_features.h"

#if defined(HAVE_SYS_AUXV_H)
#  include <sys/auxv.h>
#endif

Z_INTERNAL int PREFIX(s390_cpu_has_vx) = 0;

void Z_INTERNAL PREFIX(s390_check_features)(void) {
#if defined(S390_FEATURES)
    PREFIX(s390_cpu_has_vx) = getauxval(AT_HWCAP) & HWCAP_S390_VX;
#endif
}

#endif
