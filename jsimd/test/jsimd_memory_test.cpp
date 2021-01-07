#include <vector>
#include <type_traits>

#include "gtest/gtest.h"

#include "jsimd/config/jsimd_instruction_set.hpp"

#ifdef JSIMD_INSTR_SET_AVAILABLE

#include "jsimd/memory/jsimd_alignment.hpp"

namespace jsimd
{
    struct mock_container {};

    TEST(jsimd, alignment)
    {
        using u_vector_type = std::vector<double>;
        using a_vector_type = std::vector<double, aligned_allocator<double, JSIMD_DEFAULT_ALIGNMENT>>;

        using u_vector_align = container_alignment_t<u_vector_type>;
        using a_vector_align = container_alignment_t<a_vector_type>;
        using mock_align = container_alignment_t<mock_container>;

        EXPECT_TRUE((std::is_same<u_vector_align, unaligned_mode>::value));
        EXPECT_TRUE((std::is_same<a_vector_align, aligned_mode>::value));
        EXPECT_TRUE((std::is_same<mock_align, unaligned_mode>::value));
    }
}
#endif // JSIMD_INSTR_SET_AVAILABLE
