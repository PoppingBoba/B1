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
#include "b/util/Utility.h"

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
        StaticBuffer staticBuffer = { 0, };
        DynamicBuffer dynamicBuffer;
    };

    bool isInlined = true;
    uint64_t size = 0;

public:
    ~InlinedVector()
    {
        if (!isInlined)
        {
            free(dynamicBuffer.realBuffer);
        }
    }

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
        auto memoryMove = [&](DynamicBuffer&& buf) {
            if (dynamicBuffer.realBuffer)
            {
                memcpy(buf.realBuffer, dynamicBuffer.realBuffer, dynamicBuffer.capa);
                free(dynamicBuffer.realBuffer);
            }

            dynamicBuffer.realBuffer = buf.realBuffer;
            dynamicBuffer.capa = buf.capa;

            buf.realBuffer = nullptr;
            buf.capa = 0;
        };

        T* buffer = (isInlined)   ? reinterpret_cast<T*>(staticBuffer.realBuffer)
                                  : reinterpret_cast<T*>(dynamicBuffer.realBuffer);
        buffer[size++] = val;

        if (isInlined && size >= SIZE) 
        {
            DynamicBuffer tmpBuffer = {
                reinterpret_cast<T*>(malloc(sizeof(T) * (SIZE << 1))),
                (sizeof(T) * (SIZE << 1))
            };

            memcpy(tmpBuffer.realBuffer, buffer, (sizeof(T) * SIZE));
            memset(buffer, 0, (sizeof(T) * SIZE));

            memoryMove(b::util::Move(tmpBuffer));

            isInlined = false;
        } 
        else 
        {
            if (size >= dynamicBuffer.capa)
            {
                DynamicBuffer tmpBuffer = {
                    reinterpret_cast<T*>(malloc(sizeof(T) * (dynamicBuffer.capa << 1))),
                    (sizeof(T) * (dynamicBuffer.capa << 1))
                };
    
                memoryMove(b::util::Move(tmpBuffer));
            }
        }
    }

    T pop_back()
    {
        T* buffer = (isInlined)   ? reinterpret_cast<T*>(staticBuffer.realBuffer)
                                  : reinterpret_cast<T*>(dynamicBuffer.realBuffer);

        return buffer[size--];
    }
};

}  // namespace b::util
#endif
