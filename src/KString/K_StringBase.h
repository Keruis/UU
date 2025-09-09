#ifndef K_STRINGBASE_H
#define K_STRINGBASE_H
#include <string>

namespace Keruis::utils {

template <typename CharTy_, typename Traits_, typename AllocTy_>
class K_basic_string {
    static_assert(std::is_same_v<CharTy_, typename AllocTy_::value_type>);
    static_assert(std::is_same_v<CharTy_, typename Traits_::char_type>);

    using CharAllocType = AllocTy_;

    using AllocTraits = __gnu_cxx::__alloc_traits<AllocTy_>;

public:
    using value_type = CharTy_;
    using allocator_type = CharAllocType;
    using size_type = typename AllocTraits::size_type;
    using difference_type = typename AllocTraits::difference_type;
    using reference = typename AllocTraits::reference;
    using const_reference = typename AllocTraits::const_reference;
    using pointer = typename AllocTraits::pointer;
    using const_pointer = typename AllocTraits::const_pointer;
    using iterator = __gnu_cxx::__normal_iterator<pointer, K_basic_string>;
    using const_iterator = __gnu_cxx::__normal_iterator<const_pointer, K_basic_string>;
    using const_reverse_iterator = std::reverse_iterator<iterator>;
    using reverse_iterator = std::reverse_iterator<const_iterator>;


private:


};

}

#endif //K_STRINGBASE_H
