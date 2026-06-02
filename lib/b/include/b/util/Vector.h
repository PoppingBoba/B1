/*
 *
 *              Vector.h
 * 
 * Desc: <Vector> for b library
 * Author: Nakada Tokumei <nakada_tokumei@protonmail.com>
 * 
 */

#ifndef __B_UTIL_VECTOR_H
#define __B_UTIL_VECTOR_H

#include "b/util/Iterator.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace b::util
{

// Referenced by absl::InlinedVector
template<typename T, uint64_t SIZE = 8>
class InlinedVector
{
    struct StaticBuffer
    {
        alignas(T) uint8_t realBuffer[sizeof(T) * SIZE];
    };

    struct DynamicBuffer
    {
        T* realBuffer;
        // capacity
        uint64_t capa;
    };

    union
    {
        StaticBuffer staticBuffer;
        DynamicBuffer dynamicBuffer;
    };
    bool isInlined = true;
    uint64_t size = 0;

public:
    constexpr T& operator[](uint32_t index)
    {
        return 0;
    }

    constexpr uint32_t Size()
    {
        return size;
    }

    Iterator<T> begin()
    {
        return Iterator<T>(nullptr);
    }

    Iterator<T> end()
    {
        return Iterator<T>(nullptr);
    }

    void push_back(const T& val)
    {
        T* buffer = (isInlined)   ? reinterpret_cast<T*>(staticBuffer.realBuffer)
                                  : reinterpret_cast<T*>(dynamicBuffer.realBuffer);
        buffer[size++] = val;

        if (isInlined && size >= SIZE) 
        {
            dynamicBuffer.capa = SIZE << 1;
            dynamicBuffer.realBuffer = reinterpret_cast<T*>(malloc(dynamicBuffer.capa));
            isInlined = false;
        } 
        else 
        {
            if 
        }
    }
};

}  // namespace b::util
#endif
