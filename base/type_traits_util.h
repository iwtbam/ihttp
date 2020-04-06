#ifndef IWTBAM_TYPE_TRAITS_UTIL
#define IWTBAM_TYPE_TRAITS_UTIL

#include <type_traits>

using std::true_type;
using std::false_type;


namespace iwtbam {
namespace traits {

/*
    检测改对象是否可以迭代
*/
template<typename T>
struct iterable
{
    using has = int;
    using not_has = char;

    template<typename U>
    static has check(typename U::iterator*);

    template<typename U>
    static not_has check(...); 

    const static bool value = sizeof(check<T>(0)) == sizeof(has);
};

// namespace end
}
}

#endif