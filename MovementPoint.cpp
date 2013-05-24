/*
** MovementPoint.cpp for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:18 2013 vincent leroy
** Last update Fri May 24 18:42:53 2013 vincent leroy
*/

#include "Position.h"
#include "MovementPoint.h"

#include <cmath>

MovementPoint::MovementPoint(Position*obj) :
    AMovement(obj, MOVEMENTTYPE_POINT),
    _path()
{
}

MovementPoint::~MovementPoint()
{
}

void MovementPoint::Initialize()
{
}

void MovementPoint::Update(uint32 const diff)
{
    _owner->SetMovementFlags(0);
    if (_path.empty())
        return ;

    _owner->SetMovementFlags(MOVEMENT_FORWARD);
    point actu = point(_owner->GetPositionX(), _owner->GetPositionY());
    point dest = *_path.begin();
    float dist = _owner->GetSpeed() * diff / 1000.f;
    float maxDist = sqrt(CARRE(dest.first - actu.first) + CARRE(dest.second - actu.second));
    if (std::max(dist, maxDist) == maxDist)
    {
        _owner->UpdatePosition(dest.first, dest.second, _owner->GetOrientation());
        _path.pop_front();
        if (_path.empty())
            Finish();
    }
    else
    {
        float angle = acosf((dest.second - actu.second) / dist);
        float dx = dist * cos(angle);
        float dy = dist * sin(angle);

        _owner->UpdatePosition(actu.first + dx, actu.second + dy, angle);
    }

    _owner->HandlePositionChange();
}

void MovementPoint::Finish()
{
}

void MovementPoint::Abort(MovementTypes)
{
    _path.clear();
}

void MovementPoint::MovePoint(const point &p)
{
    PathFinderRequest request;

    request.map = NULL;
    request.width = 0;
    request.height = 0;
    request.begin = point(_owner->GetPositionX(), _owner->GetPositionY());
    request.end = p;
    request.object = this;
    request.callback = &AMovement::MovePoint;
    sPathFinder->addRequest(request);
}

void MovementPoint::MovePoint(const std::list<point> &points)
{
    _path = points;
}
