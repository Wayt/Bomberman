/*
** MapObject.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:37:58 2013 maxime ginters
** Last update Thu Jun 06 20:06:10 2013 maxime ginters
*/

#include <iostream>
#include "MapObject.h"
#include "Map.h"
#include "ObjectAI.h"
#include "Bomb.h"
#include "Client.h"

MapObject::MapObject(uint64 guid, uint32 modelId, TypeId type, std::string const& name) : GameObject(guid, modelId, name),
    _isInWorld(false), _currGrid(NULL), _typeId(type),
    _motionMaster(NULL), _owner(0), _maxBomb(2), _currBomb(0), _bombPower(10.0f),
    _telTimer(0)
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
    data << float(GetSpeed());
    data << float(GetSpeedOr());
    data << uint8(IsAlive());
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

Map const* MapObject::GetMap() const
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

    if (_telTimer > 0)
    {
        if (_telTimer <= diff)
        {
            float x, y;
            _map->GetRandomStartPosition(x, y);
            _map->TeleportPlayer(this, x, y);
            _telTimer = 0;
        }
        else
            _telTimer -= diff;
    }
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

bool MapObject::HandleHit(MapObject* obj)
{
    if (!IsAlive())
        return false;
    _alive = false;
    (void)obj;
    return true;
}

void MapObject::RegisterLua(lua_State* state)
{
    luabind::module(state) [
        luabind::class_<MapObject>("MapObject")
        .def("GetName", &MapObject::GetName)
        .def("SetSpeed", &MapObject::SetSpeed)
        .def("AddMaxBombCount", &MapObject::AddMaxBombCount)
        .def("RandomTeleport", &MapObject::RandomTeleport)
        .def("IncrBombRange", &MapObject::IncrBombRange)
        .def("Kill", &MapObject::Kill)
        .def("GetPositionX", &MapObject::GetPositionX)
        .def("GetPositionY", &MapObject::GetPositionY)
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

void MapObject::SetSpeed(float speed)
{
    GameObject::SetSpeed(speed);

    if (IsInWorld())
        _map->GridUpdater(this, GRIDUPDATE_SPEED, UPDATE_FULL);
}

void MapObject::DropBombIfPossible()
{
    if (_currBomb >= _maxBomb)
        return;

    if (_client && _client->IsFinish())
        return;

    ++_currBomb;
    float x, y, z, o;
    GetPosition(x, y, z, o);

    Bomb* bomb = new Bomb(_map->MakeNewGuid(), this);
    bomb->UpdatePosition(x, y, z, 0.0f);
    _map->AddObject(bomb);

    if (Score* sc = _map->GetScoreMgr().GetScore(GetGUID()))
    {
        sc->bomb += 1;
        _map->SendScores(GetGUID());
    }
}

void MapObject::DecreasBombCount()
{
    if (_currBomb > 0)
        --_currBomb;
}

void MapObject::HandleRespawn()
{
    GameObject::HandleRespawn();

    SetSpeed(1.0f);
    _maxBomb = 2;
    _bombPower = 10.0f;

    _map->GridUpdater(this, GRIDUPDATE_RESPAWN, UPDATE_FULL);
}

void MapObject::AddMaxBombCount(uint32 value)
{
    _maxBomb += value;
}

void MapObject::RandomTeleport()
{
    float x, y;
    _map->GetRandomStartPosition(x, y);
    _map->TeleportPlayer(this, x, y);
}

float MapObject::GetBombRange() const
{
    return _bombPower;
}

void MapObject::IncrBombRange(float value)
{
    _bombPower += value;
    if (_bombPower >= 100.0f)
        _bombPower = 100.0f;
}

void MapObject::Kill(MapObject* by)
{
    SetAlive(false);
    SetKilledBy(by->GetName());
    if (by->GetOwner() > 0)
        SetKillerGUID(by->GetOwner());
    else
        SetKillerGUID(by->GetGUID());
    SetMovementFlags(0);
    SetRespawnTime(TIME_TO_RESPAWN);
    _telTimer = TIME_TO_RESPAWN / 3;

    _map->GridUpdater(this, GRIDUPDATE_KILLED, UPDATE_FULL);

   if (Score* sc = _map->GetScoreMgr().GetScore(GetGUID()))
    {
        sc->died += 1;
        _map->SendScores(GetGUID());
    }

    if (by->GetOwner() != GetGUID())
        if (Score* sc = _map->GetScoreMgr().GetScore(by->GetOwner()))
        {
            sc->killed += 1;
            _map->SendScores(by->GetOwner());
        }
}

void MapObject::GetBoxCenter(float& blockx, float& blocky) const
{
    float x, y;
    GetPosition(x, y);
    x += 2.5f;
    y += 2.5f;

    uint32 coefx = (uint32)x / 5;
    blockx = 5 * coefx;

    uint32 coefy = (uint32)y / 5;
    blocky = 5 * coefy;
}
