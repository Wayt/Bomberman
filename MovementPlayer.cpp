/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Wed May 15 13:54:00 2013 maxime ginters
*/

#include "MovementPlayer.h"
#include "MapObject.h"

MovementPlayer::MovementPlayer(MapObject* obj) :
    AMovement(obj, MOVEMENT_PLAYER)
{}

void MovementPlayer::Initialize()
{}

void MovementPlayer::Update(uint32 const diff)
{
    (void)diff;
    // Update player position
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}