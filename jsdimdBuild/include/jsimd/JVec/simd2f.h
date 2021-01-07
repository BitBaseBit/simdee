#pragma once

#include "JVec/config.h"

#if defined(JVEC_NEON)
    #include "simd2f_neon.h"
#else
    #error No implementation defined
#endif

#include "simd2f_common.h"

#ifdef __cplusplus

    #ifdef JVEC_OSTREAM
        #include <ostream>

        JVec_inline std::ostream& operator<<(std::ostream& os, const simd2f& v) {
            os << "simd2f(" << simd2f_get_x(v) << ", "
                       << simd2f_get_y(v) << ")";
            return os;
        }
    #endif

#endif




#endif