/*
** ClientObject.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:44 2013 maxime ginters
** Last update Fri May 24 18:06:09 2013 maxime ginters
*/

#include "ClientObject.h"

ClientObject::ClientObject(uint64 guid, uint32 modelid, std::string const& name) :
    Position(), _guid(guid), _modelId(modelid), _name(name), _graphicObject(this), _motionMaster(NULL)
{
    _motionMaster = new MotionMaster(this);
    _motionMaster->Initialize(modelid == 0 ? MOVEMENTTYPE_PLAYER : MOVEMENTTYPE_IDLE);
}

ClientObject::~ClientObject()
{
    delete _motionMaster;
}

uint64 ClientObject::GetGUID() const
{
    return _guid;
}

uint32 ClientObject::GetModelId() const
{
    return _modelId;
}

GraphicObject &ClientObject::GetGraphicObject()
{
    return _graphicObject;
}

void ClientObject::Update(uint32 const diff)
{
    if (_motionMaster)
        _motionMaster->Update(diff);
}

std::string const& ClientObject::GetName() const
{
    return _name;
}
