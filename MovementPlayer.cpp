/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Thu May 16 20:47:35 2013 vincent leroy
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
    float dist = (_owner->GetSpeed() * diff) / 1000.f;
    float angle = (_owner->GetSpeedOr() * diff) / 1000.f;
    float dx = dist * cos(_owner->GetOrientation());
    float dy = dist * sin(_owner->GetOrientation());

    if (_owner->HasMovementFlag(MOVEMENT_STRAF_LEFT))
        x -= dx;
    else if (_owner->HasMovementFlag(MOVEMENT_STRAF_RIGHT))
        x += dx;

    if (_owner->HasMovementFlag(MOVEMENT_FORWARD))
        y += dy;
    else if (_owner->HasMovementFlag(MOVEMENT_BACKWARD))
        y -= dy;

    if (_owner->HasMovementFlag(MOVEMENT_TURN_LEFT))
        o += angle;
    else if (_owner->HasMovementFlag(MOVEMENT_TURN_RIGHT))
        o -= angle;

    _owner->UpdatePosition(x, y, o);
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}
