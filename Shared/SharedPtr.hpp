/*
** SharedPtr.hpp for Shared in /home/fest/Epitech/Bomberman/Shared
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 17 16:33:15 2013 maxime ginters
** Last update Fri May 17 17:20:20 2013 maxime ginters
*/

#ifndef SHAREDPTR_H_
# define SHAREDPTR_H_

#include "SharedDefines.h"

template<class T>
class SharedPtr
{
public:
    SharedPtr() :
        _ptr(NULL), _count(NULL)
    {}

    SharedPtr(T* ptr) :
        _ptr(ptr), _count(NULL)
    {
        _count = new uint32;
        *_count = 0;
    }

    SharedPtr(SharedPtr<T> const& other) :
        _ptr(other._ptr), _count(other._count)
    {
        if (_count)
           *_count += 1;
    }

    SharedPtr<T>& operator=(SharedPtr<T> const& other)
    {
        _ptr = other._ptr;
        _count = other._count;
        if (_count)
            *_count += 1;
        return *this;
    }

    SharedPtr<T>& operator=(T* other)
    {
        _ptr = other;
        _count = new uint32;
        *_count = 0;
        return *this;
    }

    ~SharedPtr()
    {
        if (!_count)
            return;
        if(*_count == 0)
        {
            delete _ptr;
            delete _count;
        }
        else
            *_count -= 1;
    }

    bool operator==(SharedPtr<T> const& other)
    {
        return _ptr == other._ptr;
    }

    T* operator->()
    {
        return _ptr;
    }

    T const* operator->() const
    {
        return _ptr;
    }

    T operator*()
    {
        return *_ptr;
    }

    bool operator!() const
    {
        return _ptr == NULL;
    }

    T* get()
    {
        return _ptr;
    }

private:
    T* _ptr;
    uint32* _count;
};

#endif /* !SHAREDPTR_H_ */
