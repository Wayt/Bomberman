/*
** MapObject.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:37:58 2013 maxime ginters
** Last update Tue May 14 17:32:57 2013 maxime ginters
*/

#include "MapObject.h"
#include "Map.h"

MapObject::MapObject(uint64 guid, uint32 modelId, TypeId type, std::string const& name) : Position(),
    _modelId(modelId), _isInWorld(false), _currGrid(NULL), _name(name), _typeId(type),
    _guid(guid)
{}

void MapObject::SetInWorld(bool in_world)
{
    _isInWorld = in_world;
}

bool MapObject::IsInWorld() const
{
    return _isInWorld;
}

uint32 MapObject::GetModelId() const
{
    return _modelId;
}

std::string const& MapObject::GetName() const
{
    return _name;
}

void MapObject::SetGrid(MapGrid* grid)
{
    if (!_map)
    {
        sLog->error("Error: call SetGrid without map ...");
        return;
    }

    if (_currGrid)
        _currGrid->RemoveObject(this);
    _currGrid = grid;
}

void MapObject::SetMap(Map* map)
{
    _map = map;
}

TypeId MapObject::GetTypeId() const
{
    return _typeId;
}

uint64 MapObject::GetGUID() const
{
    return _guid;
}

void MapObject::BuildObjectCreateForPlayer(Packet& data) const
{
    data << uint64(GetGUID());
    data << uint32(GetModelId());
    data << _name;
    data << float(GetPositionX());
    data << float(GetPositionY());
    data << float(GetPositionZ());
    data << float(GetOrientation());
}
