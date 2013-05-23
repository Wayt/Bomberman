/*
** PathFinder.h for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 13:39:07 2013 vincent leroy
** Last update Thu May 23 16:33:35 2013 maxime ginters
*/

#ifndef PATHFINDER_H_
# define PATHFINDER_H_

#include "Shared.h"
#include "PathFindingRunnable.h"

#define PATHFINDING_THREAD_COUNT 5

class PathFinder : public Singleton<PathFinder>
{
public:
    PathFinder();
    virtual ~PathFinder();

    void addRequest(const PathFinderRequest &request);
    PathFinderRequest* takeRequest();

private:
    SynchronizedQueue<PathFinderRequest> _queue;
    PathFindingRunnable *_finding[PATHFINDING_THREAD_COUNT];
};

#define sPathFinder PathFinder::instance()

#endif /* !PATHFINDER_H_ */
