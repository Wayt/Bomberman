/*
** ClientObject.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:44 2013 maxime ginters
** Last update Thu Jun 06 15:50:48 2013 maxime ginters
*/

#include "ClientObject.h"
#include "Client.h"

ClientObject::ClientObject(uint64 guid, uint32 modelid, std::string const& name) :
    GameObject(guid, modelid, name), _modelId(modelid), _name(name), _graphicObject(this), _motionMaster(NULL),
    _despawnTimer(0)
{
    _motionMaster = new MotionMaster(this);
    _motionMaster->Initialize(modelid == 0 ? MOVEMENTTYPE_PLAYER : MOVEMENTTYPE_IDLE);
}

ClientObject::~ClientObject()
{
    delete _motionMaster;
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

    if (_despawnTimer > 0)
    {
        if (_despawnTimer <= diff)
        {
            if (_client)
                _client->RemoveClientObject(this);
            _despawnTimer = 0;
        }
        else
            _despawnTimer -= diff;
    }
}

void ClientObject::HandleRespawn()
{
    SetSpeed(1.0f);
}

void ClientObject::TimedRemove(uint32 time)
{
    _despawnTimer = time;
}

MotionMaster* ClientObject::GetMotionMaster()
{
    return _motionMaster;
}
