/*
** RunRunnable.hpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 14:55:06 2013 maxime ginters
** Last update Wed May 15 17:16:49 2013 maxime ginters
*/

#ifndef RUNRUNNABLE_H_
# define RUNRUNNABLE_H_

#include <list>
#include "Shared.h"

template<class T>
class RunnablePool
{
public:
    RunnablePool() : _objList()
    {}

    void CreateThread(T& obj)
    {
        RunRunnable* run = new RunRunnable(obj);
        run->run();
        _objList.push_back(run);
    }

    void JoinAll()
    {
        typename std::list<RunRunnable*>::iterator itr = _objList.begin();
        for (; itr != _objList.end(); ++itr)
        {
            RunRunnable* run = (*itr);
            run->join();
            itr = _objList.erase(itr);
            delete run;
        }
    }

private:
    class RunRunnable : public Runnable
    {
        public:
            RunRunnable(T& obj) : _obj(obj)
            {}

            void operator()()
            {
                _obj.run();
            }
        private:
            T& _obj;
    };

    std::list<RunRunnable* > _objList;
};

#endif /* !RUNRUNNABLE_H_ */
