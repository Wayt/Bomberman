/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Wed May 29 15:54:06 2013 vincent leroy
*/

#include <iostream>
#include <cmath>

#include "Log.h"
#include "ModelMgr.h"
#include "GameObject.h"
#include "MovementPlayer.h"

MovementPlayer::MovementPlayer(GameObject* obj) :
    AMovement(obj, MOVEMENTTYPE_PLAYER)
{}

void MovementPlayer::Initialize()
{}

void MovementPlayer::Update(uint32 const diff)
{
    if (_owner->GetMovementFlags() == 0)
        return ;

    float x = _owner->GetPositionX();
    float y = _owner->GetPositionY();
    float o = _owner->GetOrientation();
    float dist = _owner->GetSpeed() * diff / 1000.f;
    float angle = (_owner->HasMovementFlag(MOVEMENT_BACKWARD) ? M_PI : 0.f) + _owner->GetOrientation();
    float dx = x;
    float dy = y;

    if (_owner->HasMovementFlag(MOVEMENT_MOVING))
    {
        dx = x + dist * cosf(angle);
        dy = y + dist * sinf(angle);

        CollisionManager(x, y, angle, dist, dx, dy);
    }

    if (_owner->HasMovementFlag(MOVEMENT_TURN_LEFT))
        o += _owner->GetSpeedOr() * diff / 1000.f;
    else if (_owner->HasMovementFlag(MOVEMENT_TURN_RIGHT))
        o -= _owner->GetSpeedOr() * diff / 1000.f;

    if (o < 0.f)
        o = M_PI * 2 + o;
    else if (o > M_PI * 2)
        o -= M_PI * 2;

    _owner->UpdatePosition(dx, dy, o);

    _owner->HandlePositionChange();
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}

void MovementPlayer::CollisionManager(float x, float y, float angle, float dist, float &dx, float &dy)
{
    std::list<const GameObject*> list;
    _owner->GetVisibleObject(list);
    ModelBox actu = sModelMgr->GetModelBoxAtPos(x, y, _owner->GetPositionZ(), _owner->GetModelId());
    ModelBox self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());

    std::list<const GameObject*>::const_iterator it;
    for (it = list.begin(); it != list.end(); ++it)
    {
        if (*it == _owner || (*it)->GetModelId() == 0)
            continue;

        try
        {
            ModelBox box = sModelMgr->GetModelBoxAtPos(*it);
            if ((actu.max.x > box.min.x && actu.min.x < box.max.x) &&
                (actu.max.y > box.min.y && actu.min.y < box.max.y))
                continue;

            if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                (self.max.y > box.min.y && self.min.y < box.max.y))
            {
                if (angle >= 0.f && angle <= M_PI_2)
                    angle = 0.f;
                else if (angle > M_PI_2 && angle <= M_PI)
                    angle = M_PI_2;
                else if (angle > M_PI && angle <= M_PI + M_PI_2)
                    angle = M_PI;
                else if (angle > M_PI + M_PI_2 && angle <= 2 * M_PI)
                    angle = M_PI + M_PI_2;

                dx = x + dist * cosf(angle);
                dy = y + dist * sinf(angle);

                self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());
                if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                    (self.max.y > box.min.y && self.min.y < box.max.y))
                {
                    if (angle >= 0.f && angle <= M_PI_2)
                        angle = M_PI_2;
                    else if (angle > M_PI_2 && angle <= M_PI)
                        angle = M_PI;
                    else if (angle > M_PI && angle <= M_PI + M_PI_2)
                        angle = M_PI + M_PI_2;
                    else if (angle > M_PI + M_PI_2 && angle <= 2 * M_PI)
                        angle = 2 * M_PI;

                    dx = x + dist * cosf(angle);
                    dy = y + dist * sinf(angle);

                    self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());
                    if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                        (self.max.y > box.min.y && self.min.y < box.max.y))
                    {
                        dx = x;
                        dy = y;
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            sLog->error("MovementPlayer : %s\n", e.what());
        }
    }
}
