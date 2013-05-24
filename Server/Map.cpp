/*
** Map.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:32:47 2013 maxime ginters
** Last update Fri May 24 20:06:26 2013 maxime ginters
*/

#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Map.h"
#include "Session.h"
#include "MapObject.h"
#include "Player.h"

Map::Map(uint32 width, uint32 height) :
    _mapGridMap(), _nextGuid(1), _width(width), _height(height)
{
    for (uint32 y = 0; y < height; y += GRID_SIZE)
        for (uint32 x = 0; x < width; x += GRID_SIZE)
            _mapGridMap.insert(
                    std::pair<std::pair<float, float>, MapGrid*>(
                        std::pair<float, float>((float)y, (float)x), new MapGrid()
                        )
                    );
}

Map* Map::CreateNewRandomMap(const uint32 width, const uint32 height, float complexity, float density)
{
    sLog->out(">> Generating random map ");

    uint32** map = new uint32*[height + 1];
    for (uint32 i = 0; i <= height; ++i)
    {
        map[i] = new uint32[width + 1];
        for (uint32 j = 0; j <= width; ++j)
            map[i][j] = 0;
    }

    uint32 shape[2];
    shape[0] = ((height / 2) * 2 + 1);
    shape[1] = ((width / 2) * 2 + 1);

    complexity = (int32)(complexity * (5 * (shape[0] + shape[1])));
    density = (int32)(density * (shape[0] / 2 * shape[1] / 2));

    #pragma omp parallel for shared(map)
    for (int32 i = 0; i < (int32)density; ++i)
    {
        uint32 x = (rand() % (shape[1] / 2)) * 2;
        uint32 y = (rand() % (shape[0] / 2)) * 2;
        map[y][x] = 1;
        if (i % ((int32)density / 10) == 0)
            sLog->out(".");

        for (int32 j = 0; j < (int32)complexity; ++j)
        {
            std::vector<std::pair<int32, int32> > neighbours;
            if (x > 1)
                neighbours.push_back(std::make_pair(y, x - 2));
            if (x < shape[1] - 2)
                neighbours.push_back(std::make_pair(y, x + 2));
            if (y > 1)
                neighbours.push_back(std::make_pair(y - 2, x));
            if (y < shape[0] - 2)
                neighbours.push_back(std::make_pair(y + 2, x));
            if (neighbours.size() > 0)
            {
                std::pair<int32, int32> pair = neighbours[rand() % neighbours.size()];
                uint32 y_ = pair.first;
                uint32 x_ = pair.second;
                if (map[y_][x_] == 0)
                {
                    map[y_][x_] = 1;
                    map[y_ + ((int32)y - (int32)y_) / 2][x_ + ((int32)x - (int32)x_) / 2] = 1;
                    x = x_;
                    y = y_;
                }
            }
        }
    }

    Map* newMap = new Map(width * MAP_PRECISION, height * MAP_PRECISION);
    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x)
        {
            if (map[y][x] == 1)
            {
                MapObject* obj = new MapObject(newMap->MakeNewGuid(), MODELID_WALL, TYPEID_OBJECT, "Wall");
                obj->UpdatePosition(x * MAP_PRECISION, y * MAP_PRECISION, 0.0f, 0.0f);
                newMap->AddObject(obj);
            }
        }
    }
    sLog->out("Map generated");

    return newMap;
}

void Map::AddObject(MapObject* obj)
{
    float x, y;
    obj->GetPosition(x, y);

    MapGrid* grid = GetGridAt(x, y);
    if (!grid)
    {
        sLog->error("Error : fail to get grid for MapObject : %s (%f - %f)", obj->GetName().c_str(), x, y);
        return;
    }

    obj->SetMap(this);
    grid->AddObject(obj);
}

void Map::RemoveObject(MapObject* obj)
{
    if (MapGrid* grid = obj->GetGrid())
    {
        grid->RemoveObject(obj);
        GridUpdater(obj, GRIDUPDATE_DELOBJ, UPDATE_FULL);
    }
    obj->SetGrid(NULL);
    obj->SetMap(NULL);
}

MapGrid::MapGrid() :
    _objectList(), _isActive(false)
{}

bool MapGrid::IsActive() const
{
    return _isActive;
}

void MapGrid::AddObject(MapObject* obj)
{
    obj->SetGrid(this);
    _objectList.push_back(obj);
}

void MapGrid::RemoveObject(MapObject* obj)
{
    _objectList.remove(obj);
}

void MapGrid::UpdateForMapObject(MapObject* obj, uint16 action)
{
    static GridUpdaterFunction updaterFunction[4] =
        {{GRIDUPDATE_ACTIVE, &MapGrid::GridUpdateActive},
        {GRIDUPDATE_SENDOBJ, &MapGrid::GridUpdateSendObject},
        {GRIDUPDATE_MOVEFLAGS, &MapGrid::GridUpdateMoveFlags},
        {GRIDUPDATE_DELOBJ, &MapGrid::GridUpdateDelObj}};

    for (uint32 i = 0; i < 4; ++i)
        if (action & updaterFunction[i].flag)
            (this->*updaterFunction[i].update)(obj);
}

void MapGrid::GridUpdateActive(MapObject *)
{
    _isActive = true;
}

void MapGrid::GridUpdateSendObject(MapObject *obj)
{
    Packet data2(SMSG_SEND_OBJECT);
    data2 << uint32(1);
    obj->BuildObjectCreateForPlayer(data2);
    BroadcastToGrid(data2, obj);

    if (obj->GetTypeId() == TYPEID_PLAYER)
    {
        std::list<MapObject*>::const_iterator itr;
        Packet data(SMSG_SEND_OBJECT);
        data << uint32(_objectList.size());
        for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        {
            (*itr)->BuildObjectCreateForPlayer(data);
        }
        obj->SendPacket(data);
    }
}

void MapGrid::GridUpdateMoveFlags(MapObject *obj)
{
    Packet data(SMSG_UPDATE_MOVEFLAGS, 12 + 4 + 4 + 4 + 4);
    data << uint64(obj->GetGUID());
    data << uint32(obj->GetMovementFlags());
    obj->WritePosition(data);
    BroadcastToGrid(data, obj);
}

void MapGrid::GridUpdateDelObj(MapObject *obj)
{
    Packet data(SMSG_DEL_OBJECT, 8);
    data << uint64(obj->GetGUID());
    BroadcastToGrid(data, obj);
}

void MapGrid::BroadcastToGrid(Packet& pkt, MapObject* except)
{
    std::list<MapObject*>::const_iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        if ((*itr)->GetTypeId() == TYPEID_PLAYER)
            if ((*itr) != except)
                (*itr)->SendPacket(pkt);
}

void MapGrid::AddObjectForUpdate(std::list<MapObject*>& list)
{
    std::list<MapObject*>::const_iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        list.push_back(*itr);
}

MapGrid* Map::GetGridAt(float x, float y)
{
    x = (float)((uint32)x - ((uint32)x % GRID_SIZE));
    y = (float)((uint32)y - ((uint32)y % GRID_SIZE));

    std::pair<float, float> index(y, x);
    std::map<std::pair<float, float>, MapGrid*>::iterator itr = _mapGridMap.find(index);
    if (itr == _mapGridMap.end())
        return NULL;
    return itr->second;
}

MapGrid const* Map::GetGridAt(float x, float y) const
{
    x = (float)((uint32)x - ((uint32)x % GRID_SIZE));
    y = (float)((uint32)y - ((uint32)y % GRID_SIZE));

    std::pair<float, float> index(y, x);
    std::map<std::pair<float, float>, MapGrid*>::const_iterator itr = _mapGridMap.find(index);
    if (itr == _mapGridMap.end())
        return NULL;
    return itr->second;
}

uint64 Map::MakeNewGuid()
{
    return _nextGuid++;
}

bool Map::_GetGridXY(MapGrid* grid, float& x, float& y) const
{
    std::map<std::pair<float, float>, MapGrid*>::const_iterator itr;
    for (itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
    {
        if (itr->second == grid)
        {
            y = itr->first.first;
            x = itr->first.second;
            return true;
        }
    }
    return false;
}

uint8 Map::BuildGridUpdaterFlags(MapGrid* old, MapGrid* newGrid) const
{
    if (!old)
        return UPDATE_FULL;

    float oldX, oldY, newX, newY;
    if (!_GetGridXY(old, oldX, oldY) || !_GetGridXY(newGrid, newX, newY))
        return 0;

    uint8 flags = 0;
    flags |= (oldY < newY ? UPDATE_UP : (oldY > newY ? UPDATE_DOWN : 0));
    flags |= (oldX < newX ? UPDATE_RIGHT : (oldX > newX ? UPDATE_LEFT : 0));
    return flags;
}

void Map::GridUpdater(MapObject* obj, uint16 action, uint8 updateFlags)
{
    float x, y;
    obj->GetPosition(x, y);

    static GridUpdateOrder updater[] = {
        {-GRID_SIZE, -GRID_SIZE, UPDATE_DOWN | UPDATE_LEFT},
        {-GRID_SIZE, 0, UPDATE_LEFT},
        {-GRID_SIZE, GRID_SIZE, UPDATE_UP | UPDATE_LEFT},
        {0, -GRID_SIZE, UPDATE_DOWN},
        {0, 0, UPDATE_CURRENT},
        {0, GRID_SIZE, UPDATE_UP},
        {GRID_SIZE, -GRID_SIZE, UPDATE_DOWN | UPDATE_RIGHT},
        {GRID_SIZE, 0, UPDATE_RIGHT},
        {GRID_SIZE, GRID_SIZE, UPDATE_UP | UPDATE_RIGHT}
    };

    for (uint8 i = 0; i < GRID_UPDATE_COUNT; ++i)
    {
        if (updater[i].flags & updateFlags)
            if (MapGrid* grid = GetGridAt(x + updater[i].x, y + updater[i].y))
                    grid->UpdateForMapObject(obj, action);
    }
}

void Map::GetWidthAndHeight(uint32& width, uint32& height) const
{
    width = _width;
    height = _height;
}

void Map::Update(uint32 const diff)
{
    std::list<MapObject*> toUpdate;
    std::map<std::pair<float, float>, MapGrid*>::iterator itr;
    for (itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        if (itr->second->IsActive())
            itr->second->AddObjectForUpdate(toUpdate);

    std::list<MapObject*>::iterator itr2;
    for (itr2 = toUpdate.begin(); itr2 != toUpdate.end(); ++itr2)
        (*itr2)->Update(diff);
}

void Map::UpdateObjectGrid(MapObject* obj)
{
    float x, y;
    obj->GetPosition(x, y);

    MapGrid* grid = GetGridAt(x, y);
    if (!grid)
        return;
    if (grid != obj->GetGrid())
        grid->AddObject(obj);
}

void MapGrid::GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const
{
    std::list<MapObject*>::const_iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        if (MapObject* tmp = (*itr))
            if (obj != tmp && tmp->GetDistance2d(obj) <= range)
                list.push_back(tmp);
}

void Map::GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const
{
    float x, y;
    obj->GetPosition(x, y);

    for (int32 iy = -GRID_SIZE; iy <= GRID_SIZE; iy += GRID_SIZE)
        for (int32 ix = -GRID_SIZE; ix <= GRID_SIZE; ix += GRID_SIZE)
            if (MapGrid const* grid = GetGridAt(x + ix, y + iy))
                grid->GetObjectListInRange(obj, range, list);
}

void Map::RegisterLua(lua_State* state)
{
    luabind::module(state) [
        luabind::class_<Map>("Map")
        .def("RemoveObject", &Map::RemoveObject)
        ];
}
