/*
** MovementPoint.h for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:21 2013 vincent leroy
** Last update Fri Jun 07 14:45:51 2013 maxime ginters
*/

#ifndef MOVEMENTPOINT_H_
# define MOVEMENTPOINT_H_

#include "MotionMaster.hpp"
#include "PathFinder.h"

class MovementPoint : public AMovement
{
public:
    MovementPoint(GameObject *obj);
    virtual ~MovementPoint();

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes);
    void MovePoint(const point &p, const Map *map);
    void MovePoint(const std::list<point> &points);
    void GetPathList(std::list<point> &path) const;

private:

    void PathGenerated(const std::list<point>& points);
    std::list<point> _path;
    bool _notified;
    Mutex _notifMutex;
};

#endif /* !MOVEMENTPOINT_H_ */
