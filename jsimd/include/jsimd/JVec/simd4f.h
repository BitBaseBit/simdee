#pragma once

#ifndef JVEC_CONFIG_H
  #include "JVec/config.h"
#endif


#ifdef JVEC_SCALAR
    #include "simd4f_scalar.h"
#elif defined(JVEC_SSE)
    #include "simd4f_sse.h"
#elif defined(JVEC_GNU)
    #include "simd4f_gnu.h"
#elif defined(JVEC_NEON)
    #include "simd4f_neon.h"
#else
    #error No implementation defined
#endif

#include "simd4f_common.h"



#ifdef __cplusplus

    #ifdef JVEC_OSTREAM
        #include <ostream>

        JVec_inline std::ostream& operator<<(std::ostream& os, const simd4f& v) {
            os << "simd4f(" << simd4f_get_x(v) << ", "
                       << simd4f_get_y(v) << ", "
                       << simd4f_get_z(v) << ", "
                       << simd4f_get_w(v) << ")";
            return os;
        }
    #endif

#endif




#endif