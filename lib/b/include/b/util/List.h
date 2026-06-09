/*
 *
 *              Vector.h
 * 
 * Desc: List for b library
 * Author: Nakada Tokumei <nakada_tokumei@protonmail.com>
 * 
 */

#ifndef __B_UTIL_LIST_H
#define __B_UTIL_LIST_H

#include "b/util/Iterator.h"
#include "b/util/Utility.h"

namespace b::util
{

template<typename T>
class LinkedList
{
public:
    struct Node
    {
        T Value;
        Node* Next;
    };

    class LinkedListIterator
    {
        Node* curr;
        
    public:
        explicit LinkedListIterator(Node* curr) : curr(curr) { }

        T& operator*() const
        {
            return curr->Value;
        }

        T* operator->() const
        {
            return &curr->Value;
        }

        LinkedListIterator& operator++() 
        {
            curr = curr->Next;
            return *this;
        }

        LinkedListIterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const LinkedListIterator& in) const
        {
            return (curr == in.curr); 
        }

        bool operator!=(const LinkedListIterator& in) const
        {
            return (curr != in.curr);
        }
    };

private:
    Node* head;

public:
    LinkedList() : head(nullptr) { }
    LinkedList(LinkedList&& in) : head(in.head) { in.head = nullptr; }
    LinkedList(const LinkedList& in) : head(nullptr)
    {
        CopyFrom(in);
    }

    ~LinkedList()
    {
        Clear();
    }

    Node* Front() { return head; }

    LinkedList<T>& PushFront(const T& val) 
    {
        head = new Node{ val, head };
        return *this;
    };

    LinkedList<T>& PushFront(T&& val) 
    {
        head = new Node{ b::util::Move(val), head };
        return *this;
    };

    LinkedList<T>& PopFront()
    {
        if (head)
        {
            auto* old = head;
            head = head->Next;
            delete old;
        }

        return *this;
    };

    // Iterator
    LinkedListIterator begin()
    {
        return LinkedListIterator(head);
    }

    LinkedListIterator end()
    {
        return LinkedListIterator(nullptr);
    }

    // Operator
    LinkedList& operator=(LinkedList&& in)
    {
        if (this != &in)
        {
            Clear();
            
            head = in.head;
            in.head = nullptr;
        }

        return *this;
    }

    LinkedList& operator=(const LinkedList& in)
    {
        if (this != &in)
        {
            Clear();

            CopyFrom(in);
        }

        return *this;
    }

private:
    void Clear()
    {
        while(head != nullptr)
            PopFront();
    }

    void CopyFrom(const LinkedList& in)
    {
        if (head)
            Clear();

        auto** tail = &head;

        auto* inHead = in.head;
        for (; inHead; inHead = inHead->Next)
        {
            *tail = new Node{ inHead->Value, nullptr };
            tail = &((*tail)->Next);
        }
    }
};

};

#endif