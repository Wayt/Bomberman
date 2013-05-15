/*
** ClientObject.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:44 2013 maxime ginters
** Last update Wed May 15 15:41:15 2013 maxime ginters
*/

#include "ClientObject.h"

ClientObject::ClientObject(uint64 guid, uint32 modelid, std::string const& name) :
    Position(), _guid(guid), _modelId(modelid), _name(name), _movementFlags(0)
{}

uint64 ClientObject::GetGUID() const
{
    return _guid;
}

void ClientObject::SetMovementFlags(uint32 flags)
{
    _movementFlags = flags;
}
