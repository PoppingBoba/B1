/*
 *
 *              Array.h
 * 
 * Desc: <Array> for b library
 * Author: Nakada Tokumei <nakada_tokumei@protonmail.com>
 * 
 */

#ifndef __B_UTIL_ARRAY_H
#define __B_UTIL_ARRAY_H

#include "b/util/Iterator.h"

#include <stdint.h>

namespace b::util
{

template<typename T, uint32_t SIZE>
class Array
{
    T _arr[SIZE];

public:
    constexpr T& operator[](uint32_t index)
    {
        return _arr[index];
    }

    constexpr uint32_t Size()
    {
        return SIZE;
    }

    Iterator<T> begin()
    {
        return Iterator<T>(reinterpret_cast<T*>(_arr));
    }

    Iterator<T> end()
    {
        return Iterator<T>(reinterpret_cast<T*>(_arr) + SIZE);
    }
};

}  // namespace b::util
#endif
