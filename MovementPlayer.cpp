/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Thu May 16 22:35:09 2013 vincent leroy
*/

#include <cmath>
#include "MovementPlayer.h"
#include "Position.h"

MovementPlayer::MovementPlayer(Position* obj) :
    AMovement(obj, MOVEMENTTYPE_PLAYER)
{}

void MovementPlayer::Initialize()
{}

void MovementPlayer::Update(uint32 const diff)
{
    float x = _owner->GetPositionX();
    float y = _owner->GetPositionY();
    float o = _owner->GetOrientation();
    float dist = _owner->GetSpeed() * diff / 1000.f;
    float angle = getAngle() + _owner->GetOrientation();
    float dx = dist * cos(angle);
    float dy = dist * sin(angle);

    if (_owner->HasMovementFlag(MOVEMENT_TURN_LEFT))
        o += _owner->GetSpeedOr() * diff / 1000.f;
    else if (_owner->HasMovementFlag(MOVEMENT_TURN_RIGHT))
        o -= _owner->GetSpeedOr() * diff / 1000.f;

    _owner->UpdatePosition(x + dx, y + dy, o);
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}

float MovementPlayer::getAngle() const
{
    float angle;

    if (_owner->HasMovementFlag(MOVEMENT_STRAF_LEFT))
    {
        if (_owner->HasMovementFlag(MOVEMENT_FORWARD))
            angle = M_PI_4;
        else if (_owner->HasMovementFlag(MOVEMENT_BACKWARD))
            angle = M_PI_2 + M_PI_4;
        else
            angle = M_PI_2;
    }
    else if (_owner->HasMovementFlag(MOVEMENT_STRAF_RIGHT))
    {
        if (_owner->HasMovementFlag(MOVEMENT_FORWARD))
            angle = M_PI + M_PI_2 + M_PI_4;
        else if (_owner->HasMovementFlag(MOVEMENT_BACKWARD))
            angle = M_PI + M_PI_4;
        else
            angle = M_PI + M_PI_2;
    }
    else
        angle = _owner->HasMovementFlag(MOVEMENT_BACKWARD) ? M_PI : 0;
    return angle;
}
