/*
** ClientObject.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:44 2013 maxime ginters
** Last update Tue May 21 15:25:07 2013 fabien casters
*/

#include "ClientObject.h"

ClientObject::ClientObject(uint64 guid, uint32 modelid, std::string const& name) :
    Position(), _guid(guid), _modelId(modelid), _name(name), _model(this), _motionMaster(NULL)
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

Model &ClientObject::GetModel()
{
    return _model;
}

void ClientObject::Update(uint32 const diff)
{
    if (_motionMaster)
        _motionMaster->Update(diff);
}
