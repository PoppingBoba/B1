/*
 *
 *              Iterator.h
 * 
 * Desc: <iterator> for b library
 * Author: Nakada Tokumei <nakada_tokumei@protonmail.com>
 * 
 */

#ifndef __B_UTIL_ITERATOR_H
#define __B_UTIL_ITERATOR_H


namespace b::util
{

template<typename T>
class Iterator
{
    T* ptr;

public:
    explicit Iterator(T* ptr) : ptr(ptr) { }

    T& operator*() const
    {
        return *ptr;
    }

    Iterator& operator++()
    {
        ++ptr;
        return *this;
    }

    bool operator!=(const Iterator<T>& in) const
    {
        return ptr != in.ptr;
    }
};

}  // namespace b::util


#endif