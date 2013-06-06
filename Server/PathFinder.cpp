/*
** PathFinder.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 13:39:00 2013 vincent leroy
** Last update Thu Jun 06 17:23:37 2013 vincent leroy
*/

#include <iostream>
#include "PathFinder.h"

PathFinder::PathFinder() :
    _queue(), _finding()
{
    for (int i = 0; i < PATHFINDING_THREAD_COUNT; ++i)
    {
        _finding[i] = new PathFindingRunnable(this);
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

