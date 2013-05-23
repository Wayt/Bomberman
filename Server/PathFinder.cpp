/*
** PathFinder.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 13:39:00 2013 vincent leroy
** Last update Thu May 23 16:34:46 2013 maxime ginters
*/

#include "PathFinder.h"

PathFinder::PathFinder() :
    _queue(), _finding(), _cond(), _mutex()
{
    for (int i = 0; i < PATHFINDING_THREAD_COUNT; ++i)
    {
        _finding[i] = new PathFindingRunnable();
        _finding[i]->run();
    }
}

PathFinder::~PathFinder()
{
    for (int i = 0; i < PATHFINDING_THREAD_COUNT; ++i)
    {
        _finding[i]->stop();
        _finding[i]->join();
    }
}

void PathFinder::addRequest(const PathFinderRequest &request)
{
    _queue.add(new PathFinderRequest(request));
}

PathFinderRequest* PathFinder::takeRequest()
{
    return _queue.get();
}

