/*
 *
 *              Stack.h
 * 
 * Desc: stack type for b library
 * Author: Nakada Tokumei <nakada_tokumei@protonmail.com>
 * 
 */

#ifndef __B_UTIL_STACK_H
#define __B_UTIL_STACK_H

#include "b/util/Iterator.h"

#include <stdint.h>

namespace b::util
{

template<typename T, uint32_t SIZE>
class Stack
{
    T _arr[SIZE];
    uint32_t _count = 0;

public:
    Stack() = default;

    constexpr T& operator[](uint32_t index)
    {
        auto realIndex = (index > _count) ? _count : index; 
        return _arr[realIndex];
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
        return Iterator<T>(reinterpret_cast<T*>(_arr) + _count);
    }


    Stack& push(T val)
    {
        if (_count < SIZE)
            _arr[_count++] = val;

        return *this;
    }

    Stack& pop()
    {
        if (_count > 0)
            _count--;

        return *this;
    }

    uint32_t Count() { return _count; }
};
 
}  // namespace b::util
#endif
 