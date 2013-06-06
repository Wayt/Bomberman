/*
** MovementPoint.h for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:21 2013 vincent leroy
** Last update Thu Jun 06 15:22:31 2013 maxime ginters
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

private:

    void PathGenerated(const std::list<point>& points);
    std::list<point> _path;
};

#endif /* !MOVEMENTPOINT_H_ */
