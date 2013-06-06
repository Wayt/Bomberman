/*
** MovementPoint.cpp for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu May 23 16:38:18 2013 vincent leroy
** Last update Thu Jun 06 22:56:49 2013 vincent leroy
*/

#include "GameObject.h"
#include "MovementPoint.h"
#include "Map.h"

#include <cmath>

MovementPoint::MovementPoint(GameObject *obj) :
    AMovement(obj, MOVEMENTTYPE_POINT),
    _path(), _notified(false), _notifMutex()
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
        return;
    {
        ScopLock lock(_notifMutex);
        if (!_notified)
        {
            if (_path.size() > 0)
                _owner->HandlePathGenerated(_path);
            else
                _owner->HandleFailToCreatePath();
            _notified = true;
        }
    }

    _owner->SetMovementFlags(MOVEMENT_FORWARD);
    point actu = point(_owner->GetPositionX(), _owner->GetPositionY());
    point dest = *_path.begin();
    float dist = _owner->GetSpeed() * 10.0f * diff / 1000.f;
    float maxDist = std::sqrt(CARRE(dest.first - actu.first) + CARRE(dest.second - actu.second));

    if (dist > maxDist)
        _path.pop_front();
    else if (maxDist > 0.0f)
    {
        float x = dest.first - actu.first;
        float y = dest.second - actu.second;
        float k = std::sqrt(CARRE(dist) / (CARRE(x) + CARRE(y)));

        float dx = x * k;
        float dy = y * k;
        float angle = atan2f(dy, dx);

        dx += actu.first;
        dy += actu.second;
        if (dx != dx || dy != dy)
        {
            std::cout << "NAN NAN NAN NAN NAN NAN NAN NAN NAN NAN NAN" << std::endl;
            _owner = NULL;
        }
        _owner->UpdatePosition(dx, dy, angle);

        _owner->HandlePositionChange();
    }
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

    request.map = new uint8*[map->GetHeight() / MAP_PRECISION];
    for (uint32 i = 0; i < map->GetHeight() / MAP_PRECISION; ++i)
    {
        request.map[i] = new uint8[map->GetWidth() / MAP_PRECISION];
        for (uint32 j = 0; j < map->GetWidth() / MAP_PRECISION; ++j)
            request.map[i][j] = 0;
    }

    std::list<GameObject*>::const_iterator it;
    for (it = list.begin(); it != list.end(); ++it)
    {
        float x, y;
        (*it)->GetPosition(x, y);
        if ((*it)->GetModelId() == MODELID_WALL || (*it)->GetModelId() == MODELID_BORDER)
            request.map[(uint32)y / MAP_PRECISION][(uint32)x / MAP_PRECISION] = 1;
        else
            request.map[(uint32)y / MAP_PRECISION][(uint32)x / MAP_PRECISION] = 0;
    }

    request.width = map->GetWidth() / MAP_PRECISION;
    request.height = map->GetHeight() / MAP_PRECISION;
    float x, y;
    _owner->GetPosition(x, y);
    x += 2.5f;
    y += 2.5f;
    x = ((uint32)x / MAP_PRECISION) * MAP_PRECISION;
    y = ((uint32)y / MAP_PRECISION) * MAP_PRECISION;

    request.begin = point(x / MAP_PRECISION, y / MAP_PRECISION);

    x = p.first;
    y = p.second;
    x += 2.5f;
    y += 2.5f;
    x = ((uint32)x / MAP_PRECISION) * MAP_PRECISION;
    y = ((uint32)y / MAP_PRECISION) * MAP_PRECISION;

    request.end = point(x / MAP_PRECISION, y / MAP_PRECISION);
    request.object = this;
    request.callback = &MovementPoint::PathGenerated;

    for (uint32 y = 0; y < map->GetHeight() / MAP_PRECISION; ++y)
    {
        for (uint32 x = 0; x < map->GetWidth() / MAP_PRECISION; ++x)
        {
            if (x == request.begin.first && request.begin.second == y)
                std::cout << "B ";
            else if (x == request.end.first && request.end.second == y)
                std::cout << "E ";
            else
                std::cout << uint32(request.map[y][x]) << " ";
        }
            std::cout << std::endl;
    }

    if (request.begin != request.end)
        sPathFinder->addRequest(request);
    else
        Finish();
}

void MovementPoint::GetPath(std::list<point> &path) const
{
    path = _path;
}

void MovementPoint::PathGenerated(const std::list<point>& points)
{
    ScopLock lock(_notifMutex);;
    _path = points;
    _notified = false;
}

void MovementPoint::MovePoint(const std::list<point> &points)
{
    _path = points;
}
