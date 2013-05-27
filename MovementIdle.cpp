/*
** MovementIdle.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:28:45 2013 maxime ginters
** Last update Mon May 27 18:42:07 2013 vincent leroy
*/

#include "MovementIdle.h"
#include "Position.h"

MovementIdle::MovementIdle(GameObject* obj) :
    AMovement(obj, MOVEMENTTYPE_IDLE)
{}

void MovementIdle::Initialize()
{}

void MovementIdle::Update(uint32 const diff)
{
    (void)diff;
}

void MovementIdle::Finish()
{}

void MovementIdle::Abort(MovementTypes newType)
{
    (void)newType;
}
