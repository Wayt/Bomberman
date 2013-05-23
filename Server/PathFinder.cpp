/*
** PathFinder.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 13:39:00 2013 vincent leroy
** Last update Thu May 23 15:33:09 2013 vincent leroy
*/

#include "PathFinder.h"

PathFinder::PathFinder() :
    _queue(), _finding()
{
    for (int i = 0; i < NB_PATHFINDING; ++i)
    {
        _finding[i] = new PathFindingRunnable();
        _finding[i]->run();
    }
}

PathFinder::~PathFinder()
{
}

void PathFinder::addRequest(const PathFinderRequest &request)
{
    _queue.add(new PathFinderRequest(request));
}

PathFinderRequest* PathFinder::takeRequest()
{
    return _queue.get();
}

void PathFinder::requestFinished(PathFinderRequest *request)
{
    delete request;
}
