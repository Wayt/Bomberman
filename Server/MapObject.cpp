/*
** MapObject.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:37:58 2013 maxime ginters
** Last update Wed Jun 05 18:59:09 2013 maxime ginters
*/

#include <iostream>
#include "MapObject.h"
#include "Map.h"
#include "ObjectAI.h"

MapObject::MapObject(uint64 guid, uint32 modelId, TypeId type, std::string const& name) : GameObject(guid, modelId, name),
    _isInWorld(false), _currGrid(NULL), _typeId(type),
    _motionMaster(NULL), _owner(0)
{
    _motionMaster = new MotionMaster(this);
    _motionMaster->Initialize(modelId == MODELID_PLAYER ? MOVEMENTTYPE_PLAYER : MOVEMENTTYPE_IDLE);
}

MapObject::~MapObject()
{
    delete _motionMaster;
}

void MapObject::SetInWorld(bool in_world)
{
    _isInWorld = in_world;
}

bool MapObject::IsInWorld() const
{
    return _isInWorld;
}

void MapObject::SetGrid(MapGrid* grid)
{
    if (!_map)
    {
        sLog->error("Error: call SetGrid without map ...");
        return;
    }

    MapGrid*  oldGrid = _currGrid;
    if (_currGrid)
        _currGrid->RemoveObject(this);
    _currGrid = grid;

    if (_map && grid)
    {
        uint8 flags = _map->BuildGridUpdaterFlags(oldGrid, _currGrid);
        _map->GridUpdater(this, GRIDUPDATE_SENDOBJ, flags);
    }
}

void MapObject::SetMap(Map* map)
{
    _map = map;
    SetInWorld(_map == NULL ? false : true);
}

TypeId MapObject::GetTypeId() const
{
    return _typeId;
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
    data << uint64(_owner);
}


MotionMaster const* MapObject::GetMotionMaster() const
{
    return _motionMaster;
}

MotionMaster* MapObject::GetMotionMaster()
{
    return _motionMaster;
}

void MapObject::SendPacket(Packet const& data)
{
    (void)data;
}

Map* MapObject::GetMap()
{
    return _map;
}

MapGrid* MapObject::GetGrid()
{
    return _currGrid;
}

void MapObject::Update(uint32 const diff)
{
    if (_motionMaster)
        _motionMaster->Update(diff);
    UpdateRespawnTime(diff);
}

void MapObject::HandlePositionChange()
{
    if (!IsInWorld())
        return;

    if (_map)
        _map->UpdateObjectGrid(this);
}

uint64 MapObject::GetOwner()
{
    return _owner;
}

void MapObject::SetOwner(uint64 guid)
{
    _owner = guid;
}

void MapObject::GetObjectListInRange(float range, std::list<MapObject*>& list) const
{
    if (!_map)
        return;
    _map->GetObjectListInRange(this, range, list);
}

std::list<MapObject*> MapObject::GetObjectListInRange(float range)
{
    std::list<MapObject*> list;
    GetObjectListInRange(range, list);
    return list;
}

ObjectAI* MapObject::GetAI()
{
    return NULL;
}

void MapObject::HandleHit(MapObject* obj)
{
    _alive = false;
    (void)obj;
}

void MapObject::RegisterLua(lua_State* state)
{
    luabind::module(state) [
        luabind::class_<MapObject>("MapObject")
        .def("GetName", &MapObject::GetName)
        ];
}

std::ofstream& operator<<(std::ofstream& stream, MapObject const* obj)
{
    stream << *obj;
    return stream;
}

std::ofstream& operator<<(std::ofstream& stream, MapObject const& obj)
{
    stream << obj.GetModelId() << "," << obj.GetName() << "," << obj.GetSpeed() << "," << obj.GetSpeedOr() << "," << obj.GetPositionX() << "," << obj.GetPositionY() << "," << obj.GetPositionZ() << "," << obj.GetOrientation() << "," << obj.GetGUID();
    return stream;
}
