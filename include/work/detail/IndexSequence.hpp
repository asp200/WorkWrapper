#ifndef INDEX_SEQUENCE_HPP_
#define INDEX_SEQUENCE_HPP_

// Standard includes.
#include<cstddef>

namespace work
{
    namespace detail
    {
        /// The index sequence.
        template<std::size_t... Ts>
        struct index_sequence {};

        /// Recursion case.
        template <std::size_t N, std::size_t... Ts>
        struct make_index_sequence : make_index_sequence<N-1, N-1, Ts...> {};

        /// Recursion abort.
        template <std::size_t... Ts>
        struct make_index_sequence<0, Ts...> : index_sequence<Ts...>
        {
            using type = index_sequence<Ts...>;
        };
    }
}

#endif /* INDEX_SEQUENCE_HPP_ */
