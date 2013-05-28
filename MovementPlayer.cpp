/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Tue May 28 16:04:53 2013 maxime ginters
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
    float angle = MovementPlayer::getAngle(_owner) + _owner->GetOrientation();
    float dx = x;
    float dy = y;

    if (_owner->HasMovementFlag(MOVEMENT_MOVING))
    {
        dx = x + dist * cosf(angle);
        dy = y + dist * sinf(angle);

        /*
        std::list<const GameObject*> list;
        _owner->GetVisibleObject(list);
        ModelBox self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());

        std::list<const GameObject*>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            if (*it == _owner)
                continue;

            try
            {
                ModelBox box = sModelMgr->GetModelBoxAtPos(*it);
                if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                    (self.max.y > box.min.y && self.min.y < box.max.y))
                {
                    dx = x;
                    dy = y;
                    break;
                }
            }
            catch (const std::exception &e)
            {
                sLog->error("MovementPlayer : %s\n", e.what());
            }
        }*/
    }

    if (_owner->HasMovementFlag(MOVEMENT_TURN_LEFT))
        o += _owner->GetSpeedOr() * diff / 1000.f;
    else if (_owner->HasMovementFlag(MOVEMENT_TURN_RIGHT))
        o -= _owner->GetSpeedOr() * diff / 1000.f;

    _owner->UpdatePosition(dx, dy, o);

    _owner->HandlePositionChange();
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}

float MovementPlayer::getAngle(const GameObject *owner)
{
    float angle = 0.f;

    if (owner->HasMovementFlag(MOVEMENT_STRAF_LEFT))
    {
        if (owner->HasMovementFlag(MOVEMENT_FORWARD))
            angle = M_PI_4;
        else if (owner->HasMovementFlag(MOVEMENT_BACKWARD))
            angle = M_PI_2 + M_PI_4;
        else
            angle = M_PI_2;
    }
    else if (owner->HasMovementFlag(MOVEMENT_STRAF_RIGHT))
    {
        if (owner->HasMovementFlag(MOVEMENT_FORWARD))
            angle = M_PI + M_PI_2 + M_PI_4;
        else if (owner->HasMovementFlag(MOVEMENT_BACKWARD))
            angle = M_PI + M_PI_4;
        else
            angle = M_PI + M_PI_2;
    }
    else
        angle = (owner->HasMovementFlag(MOVEMENT_BACKWARD) ? M_PI : 0.f);
    return angle;
}
