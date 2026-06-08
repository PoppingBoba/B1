#ifndef __B_UTIL_UTILITY_H
#define __B_UTIL_UTILITY_H

#include "b/util/TypeTraits.h"

namespace b::util
{

template<typename T>
constexpr b::util::remove_reference_t<T>&&
Move(T&& v)
{
    return static_cast<b::util::remove_reference_t<T>&&>(v);
}

};

#endif