/*
** LockedList.hpp for Shared in /home/fest/Epitech/Bomberman/Shared
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:52:59 2013 maxime ginters
** Last update Fri May 10 15:53:27 2013 maxime ginters
*/

#ifndef LOCKEDLIST_H_
# define LOCKEDLIST_H_

#include <list>
#include "Mutex.h"
#include "ScopLock.h"

template<class T>
class LockedQueue
{
public:
    void add(T* data)
    {
        ScopLock lock(_mutex);
        _queue.push(data);
    }

    T* get()
    {
        ScopLock lock(_mutex);
        if (_queue.empty())
            return NULL;
        T* data = _queue.front();
        _queue.pop();
        return data;
    }

    uint32 size()
    {
        ScopLock lock(_mutex);
        return _queue.size();
    }

    bool empty()
    {
        ScopLock lock(_mutex);
        return _queue.empty();
    }

private:
    Mutex _mutex;
    std::list<T*> _queue;
};

#endif /* !LOCKEDLIST_H_ */
