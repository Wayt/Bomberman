/*
** MovementPoint.h for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:21 2013 vincent leroy
** Last update Fri May 24 16:12:56 2013 vincent leroy
*/

#ifndef MOVEMENTPOINT_H_
# define MOVEMENTPOINT_H_

#include "MotionMaster.hpp"
#include "PathFinder.h"

class MovementPoint : public AMovement
{
public:
    MovementPoint(Position*obj);
    virtual ~MovementPoint();

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes);
    void MovePoint(const point &p);
    void MovePoint(const std::list<point> &points);

private:
    std::list<point> _path;
};

#endif /* !MOVEMENTPOINT_H_ */
