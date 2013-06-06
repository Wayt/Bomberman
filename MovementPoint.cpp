/*
** MovementPoint.cpp for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:18 2013 vincent leroy
** Last update Thu Jun 06 20:01:07 2013 vincent leroy
*/

#include "GameObject.h"
#include "MovementPoint.h"
#include "Map.h"

#include <cmath>

MovementPoint::MovementPoint(GameObject *obj) :
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
    float dist = _owner->GetSpeed() * 10.0f * diff / 1000.f;
    float maxDist = std::sqrt(CARRE(dest.first - actu.first) + CARRE(dest.second - actu.second));

    if (dist > maxDist)
        _path.pop_front();

    float x = dest.first - actu.first;
    float y = dest.second - actu.second;
    float k = std::sqrt(CARRE(dist) / (CARRE(x) + CARRE(y)));

    float dx = x * k;
    float dy = y * k;
    float angle = atan2f(dy, dx);

    _owner->UpdatePosition(actu.first + dx, actu.second + dy, angle);

    _owner->HandlePositionChange();
    if (_path.empty())
        Finish();
}

void MovementPoint::Finish()
{
    _owner->HandleFinishMovePoint();
}

void MovementPoint::Abort(MovementTypes)
{
    _path.clear();
}

void MovementPoint::MovePoint(const point &p, const Map *map)
{
    PathFinderRequest request;

    std::list<GameObject*> list;
    map->GetAllObject(list);

    request.map = new uint8*[map->GetHeight()];
    for (uint32 i = 0; i < map->GetHeight(); ++i)
    {
        request.map[i] = new uint8[map->GetWidth()];
        for (uint32 j = 0; j < map->GetWidth(); ++j)
            request.map[i][j] = 0;
    }

    std::list<GameObject*>::const_iterator it;
    for (it = list.begin(); it != list.end(); ++it)
    {
        float x, y;
        (*it)->GetPosition(x, y);
        if ((*it)->GetModelId() == MODELID_WALL || (*it)->GetModelId() == MODELID_BORDER)
            request.map[(uint32)x / MAP_PRECISION][(uint32)y / MAP_PRECISION] = 1;
        else
            request.map[(uint32)x / MAP_PRECISION][(uint32)y / MAP_PRECISION] = 0;
    }

    request.width = map->GetWidth();
    request.height = map->GetHeight();
    request.begin = point(_owner->GetPositionX(), _owner->GetPositionY());
    request.end = p;
    request.object = this;
    request.callback = &MovementPoint::PathGenerated;
    sPathFinder->addRequest(request);
}

void MovementPoint::GetPath(std::list<point> &path) const
{
    path = _path;
}

void MovementPoint::PathGenerated(const std::list<point>& points)
{
    _path = points;
    if (points.size() > 0)
        _owner->HandlePathGenerated(points);
    else
        _owner->HandleFailToCreatePath();
}

void MovementPoint::MovePoint(const std::list<point> &points)
{
    _path = points;
}
