#ifndef __B_UTIL_TYPETRAITS_H
#define __B_UTIL_TYPETRAITS_H

namespace b::util
{

template<typename T>
struct remove_reference
{
    using type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template<typename T>
using remove_reference_t = remove_reference<T>::type;

}

#endif