/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Mon May 27 19:40:35 2013 vincent leroy
*/

#include <iostream>
#include <cmath>

#include "Log.h"
#include "ModelMgr.h"
#include "MovementPlayer.h"
#include "GameObject.h"

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
    float dx = 0.f;
    float dy = 0.f;

    if (_owner->HasMovementFlag(MOVEMENT_MOVING))
    {
        dx = x + dist * cos(angle);
        dy = y + dist * sin(angle);
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
