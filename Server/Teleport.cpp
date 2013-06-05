/*
** Teleport.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 22:15:34 2013 vincent leroy
** Last update Wed Jun 05 22:18:35 2013 vincent leroy
*/

#include "Teleport.h"

Teleport::Teleport(uint64 guid) :
    Object(guid, MODELID_TELEPORT, "Teleporter")
{
    InitializeAI("Scripts/teleport.lua");
}

Teleport::~Teleport()
{
}
