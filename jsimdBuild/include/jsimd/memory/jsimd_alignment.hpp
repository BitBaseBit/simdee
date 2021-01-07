#ifndef JSIMD_ALIGNMENT_HPP
#define JSIMD_ALIGNMENT_HPP

#include "../config/jsimd_align.hpp"
#include "jsimd_aligned_allocator.hpp"

namespace jsimd
{
    /**
    * @struct aligned_mode
    * @brief tag for load and store of aligned memory.
    */
    struct aligned_mode
    {
    };

    /**
    * @struct unaligned_mode
    * @brief tag for load and store of unaligned memory.
    */
    struct unaligned_mode
    {
    };

    /***********************
     * Allocator alignment *
     ***********************/

    template <class A>
    struct allocator_alignment
    {
        using type = unaligned_mode;
    };

#if defined(JSIMD_DEFAULT_ALIGNMENT)
    template <class T>
    struct allocator_alignment<aligned_allocator<T, JSIMD_DEFAULT_ALIGNMENT>>
    {
        using type = aligned_mode;
    };
#endif

    template <class A>
    using allocator_alignment_t = typename allocator_alignment<A>::type;

    /***********************
     * container alignment *
     ***********************/

    namespace detail
    {
        template <class T>
        struct void_t
        {
            using type = void;
        };
    }

    template <class C, class = void>
    struct container_alignment
    {
        using type = unaligned_mode;
    };

    template <class C>
    struct container_alignment<C, typename detail::void_t<typename C::allocator_type>::type>
    {
        using type = allocator_alignment_t<typename C::allocator_type>;
    };

    template <class C>
    using container_alignment_t = typename container_alignment<C>::type;

}

#endif
