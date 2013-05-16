/*
** ClientObject.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:44 2013 maxime ginters
** Last update Thu May 16 19:16:55 2013 vincent leroy
*/

#include "ClientObject.h"

ClientObject::ClientObject(uint64 guid, uint32 modelid, std::string const& name) :
    Position(), _guid(guid), _modelId(modelid), _name(name), _model(this)
{}

uint64 ClientObject::GetGUID() const
{
    return _guid;
}

Model &ClientObject::GetModel()
{
    return _model;
}
