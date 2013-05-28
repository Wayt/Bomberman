/*
** SharedPtr.hpp for Shared in /home/fest/Epitech/Bomberman/Shared
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 17 16:33:15 2013 maxime ginters
** Last update Tue May 28 19:46:01 2013 maxime ginters
*/

#ifndef SHAREDPTR_H_
# define SHAREDPTR_H_

#include "ScopLock.h"
#include "SharedDefines.h"

template<class T>
class SharedPtr
{
public:
    SharedPtr() : _data(NULL), _ref(NULL)
    {
        _ref = new RefCounter();
        _ref->Add();
    }

    SharedPtr(T* val) : _data(val), _ref(NULL)
    {
        _ref = new RefCounter();
        _ref->Add();
    }

    SharedPtr(SharedPtr<T> const& other) : _data(other._data), _ref(other._ref)
    {
        _ref->Add();
    }

    ~SharedPtr()
    {
        if (_ref->Release() == 0)
        {
            delete _data;
            delete _ref;
        }
    }

    T& operator*()
    {
        return *_data;
    }

    T* operator->()
    {
        return _data;
    }

    SharedPtr<T>& operator=(SharedPtr<T> const& other)
    {
        if (this != &other)
        {
            if (_ref->Release() == 0)
            {
                delete _data;
                delete _ref;
            }

            _data = other._data;
            _ref = other._ref;
            _ref->Add();
        }
        return *this;
    }

    T* get()
    {
        return _data;
    }


    bool operator==(SharedPtr<T> const& other)
    {
        return _data == other._data;
    }

    T const* operator->() const
    {
        return _data;
    }

    bool operator!() const
    {
        return _data == NULL;
    }


private:
    class RefCounter
    {
    public:
        void Add()
        {
            ScopLock lock(_mutex);
            ++_count;
        }
        uint32 Release()
        {
            ScopLock lock(_mutex);
            return --_count;
        }
    private:
        Mutex _mutex;
        uint32 _count;
    };

    T* _data;
    RefCounter* _ref;
};

#endif /* !SHAREDPTR_H_ */
