/*
** GameObject.cpp for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon May 27 18:26:51 2013 vincent leroy
** Last update Wed May 29 15:29:39 2013 maxime ginters
*/

#include "Map.h"
#include "Client.h"
#include "GameObject.h"

GameObject::GameObject(uint32 modelId, const std::string &name) :
    Position(),
    _modelId(modelId), _name(name),
    _speed(10.f), _speed_or(1.f),
    _movementFlags(0), _map(NULL),
    _client(NULL)
{
}

GameObject::~GameObject()
{
}

uint32 GameObject::GetMovementFlags() const
{
    return _movementFlags;
}

void GameObject::SetMovementFlags(uint32 flags)
{
    _movementFlags = flags;
}

bool GameObject::AddMovementFlag(uint32 flag)
{
    if (_movementFlags & flag)
        return false;
    _movementFlags |= flag;
    return true;
}

bool GameObject::RemoveMovementFlag(uint32 flag)
{
    if (!(_movementFlags & flag))
        return false;
    _movementFlags &= ~flag;
    return true;
}

bool GameObject::UpdateMovementFlag(uint32 flag, bool add)
{
    if (add)
        return AddMovementFlag(flag);
    else
        return RemoveMovementFlag(flag);
}

bool GameObject::HasMovementFlag(uint32 flag) const
{
    return (_movementFlags & flag);
}

void GameObject::SetSpeed(float speed)
{
    _speed = speed;
}

float GameObject::GetSpeed() const
{
    return _speed;
}

void GameObject::SetSpeedOr(float speed_or)
{
    _speed_or = speed_or;
}

float GameObject::GetSpeedOr() const
{
    return _speed_or;
}

uint32 GameObject::GetModelId() const
{
    return _modelId;
}

void GameObject::SetMap(Map *map)
{
    _map = map;
}

void GameObject::SetClient(Client *client)
{
    _client = client;
}

Map* GameObject::GetMap()
{
    return _map;
}

Client* GameObject::GetClient()
{
    return _client;
}

void GameObject::GetVisibleObject(std::list<const GameObject*> &list) const
{
    if (_client)
        _client->GetObjectList(list);
    else if (_map)
        _map->GetObjectList(this, list);
}

std::string const& GameObject::GetName() const
{
    return _name;
}
