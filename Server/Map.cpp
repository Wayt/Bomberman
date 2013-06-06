/*
** Map.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:32:47 2013 maxime ginters
** Last update Thu Jun 06 13:07:12 2013 maxime ginters
*/

#include <cstdlib>
#include <vector>
#include <algorithm>

#include "ModelMgr.h"
#include "Map.h"
#include "Session.h"
#include "MapObject.h"
#include "Player.h"
#include "Object.h"

#define BORDER_DENSITY 5

Map::Map(uint32 width, uint32 height, uint32 nguid, uint32 time) :
    _mapGridMap(), _nextGuid(nguid), _width(width), _height(height), _removeList(),
    _gameTimer(time)
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

    srand(time(NULL));

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
                    if ((rand() * y_ * x_) % 2 == 0)
                        map[y_][x_] = 2;
                    map[y_ + ((int32)y - (int32)y_) / 2][x_ + ((int32)x - (int32)x_) / 2] = 1;
                    x = x_;
                    y = y_;
                }
            }
        }
    }

    for (uint32 i = 0; i < height; ++i)
    {
        map[i][0] = 2;
        map[i][width - 1] = 2;
    }

    for (uint32 i = 0; i < width; ++i)
    {
        map[0][i] = 2;
        map[height - 1][i] = 2;
    }

    for (uint32 i = 0; i < height; i += BORDER_DENSITY)
        for (uint32 j = 0; j < width; j += BORDER_DENSITY)
            map[i][j] = 2;

    Map* newMap = new Map(width * MAP_PRECISION, height * MAP_PRECISION);
    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x)
        {
            if (map[y][x] == 1)
            {
                Object* obj = new Object(newMap->MakeNewGuid(), MODELID_WALL, "Wall");
                obj->InitializeAI("Scripts/wall.lua");
                obj->UpdatePosition(x * MAP_PRECISION, y * MAP_PRECISION, 0.0f, 0.0f);
                newMap->AddObject(obj);
            }
            else if (map[y][x] == 2)
            {
                Object *obj = new Object(newMap->MakeNewGuid(), MODELID_BORDER, "Border");
                obj->InitializeAI("Scripts/border.lua");
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

    if (obj->GetTypeId() == TYPEID_PLAYER)
    {
        Packet data(SMSG_PLAYER_JOIN, 8 + obj->GetName().size());
        data << uint64(obj->GetGUID());
        data << obj->GetName();
        BroadcastToAll(data);
    }
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
    _removeList.push_back(obj);

    if (obj->GetTypeId() == TYPEID_PLAYER)
    {
        Packet data(SMSG_PLAYER_LEAVE, 8 + obj->GetName().size());
        data << uint64(obj->GetGUID());
        data << obj->GetName();
        BroadcastToAll(data);
    }
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
    static GridUpdaterFunction updaterFunction[9] = {
        {GRIDUPDATE_ACTIVE, &MapGrid::GridUpdateActive},
        {GRIDUPDATE_SENDOBJ, &MapGrid::GridUpdateSendObject},
        {GRIDUPDATE_MOVEFLAGS, &MapGrid::GridUpdateMoveFlags},
        {GRIDUPDATE_DELOBJ, &MapGrid::GridUpdateDelObj},
        {GRIDUPDATE_KILLED, &MapGrid::GridUpdateKilled},
        {GRIDUPDATE_RESPAWN, &MapGrid::GridUpdateRespawn},
        {GRIDUPDATE_TELEPORT, &MapGrid::GridUpdateTeleport},
        {GRIDUPDATE_SPEED, &MapGrid::GridUpdateSpeed},
        {GRIDUPDATE_BOUM, &MapGrid::GridUpdateBoum}
    };

    for (uint32 i = 0; i < 9; ++i)
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

void MapGrid::GridUpdateKilled(MapObject *obj)
{
    Packet data(SMSG_PLAYER_KILLED, 8 + 4 + obj->GetLastKiller().length() + 8);
    data << uint64(obj->GetGUID());
    data << uint32(obj->GetRespawnTime());
    data << obj->GetLastKiller();
    data << uint64(obj->GetLastKillerGUID());
    BroadcastToGrid(data, NULL);
}

void MapGrid::GridUpdateRespawn(MapObject *obj)
{
    Packet data(SMSG_PLAYER_RESPAWN, 8);
    data << uint64(obj->GetGUID());
    BroadcastToGrid(data, NULL);
}

void MapGrid::GridUpdateTeleport(MapObject *obj)
{
    Packet data(SMSG_TELEPORT, 8 + 16);
    data << uint64(obj->GetGUID());
    obj->WritePosition(data);
    BroadcastToGrid(data, NULL);
}

void MapGrid::GridUpdateSpeed(MapObject* obj)
{
    Packet data(SMSG_UPDATE_SPEED, 8 + 4 + 16);
    data << uint64(obj->GetGUID());
    data << float(obj->GetSpeed());
    obj->WritePosition(data);
    BroadcastToGrid(data, NULL);
}

void MapGrid::GridUpdateBoum(MapObject* obj)
{
    Packet data(SMSG_BOMB_BOUMED, 8 + 4);
    data << uint64(obj->GetGUID());
    data << float(obj->GetBombRange());
    BroadcastToGrid(data, NULL);
}

void MapGrid::BroadcastToGrid(Packet const& pkt, MapObject* except)
{
    std::list<MapObject*>::const_iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        if ((*itr)->GetTypeId() == TYPEID_PLAYER)
            if ((*itr) != except)
                (*itr)->SendPacket(pkt);
}

void MapGrid::AddObjectForUpdate(std::list<MapObject*>& list) const
{
    std::list<MapObject*>::const_iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        list.push_back(*itr);
}

void MapGrid::GetObjectList(std::list<GameObject*> &list) const
{
    std::list<MapObject*>::const_iterator it;
    for (it = _objectList.begin(); it != _objectList.end(); ++it)
        list.push_back(*it);
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

    if (std::abs(oldX - newX) > GRID_SIZE || std::abs(oldY - newY) > GRID_SIZE)
        return UPDATE_FULL;

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

uint32 Map::GetWidth() const
{
    return _width;
}

uint32 Map::GetHeight() const
{
    return _height;
}

void Map::Update(uint32 const diff)
{
    if (IsFinish())
        return;

    if (_gameTimer <= diff)
    {
        HandleGameFinish();
        _gameTimer = 0;
        return;
    }
    else
        _gameTimer -= diff;
    std::list<MapObject*> toUpdate;
    std::map<std::pair<float, float>, MapGrid*>::iterator itr;
    for (itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        if (itr->second->IsActive())
            itr->second->AddObjectForUpdate(toUpdate);

    std::list<MapObject*>::iterator itr2;
    for (itr2 = toUpdate.begin(); itr2 != toUpdate.end(); ++itr2)
        if (MapObject* obj = *itr2)
            if (obj->IsInWorld())
                obj->Update(diff);

    std::list<MapObject*>::iterator next;
    for (itr2 = _removeList.begin(); itr2 != _removeList.end(); itr2 = next)
    {
        next = itr2;
        ++next;
        _removeList.erase(itr2);
        delete *itr2;

    }
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

uint32 MapGrid::GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const
{
    uint32 i = 0;
    std::list<MapObject*>::const_iterator itr;
    range *= range;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        if (MapObject* tmp = (*itr))
            if (obj != tmp && tmp->GetDistance2dSquare(obj) <= range)
	    {
                list.push_back(tmp);
		i++;
	    }
    return i;
}

uint32 MapGrid::GetObjectListInRange(float x, float y, float range, std::list<MapObject*>& list) const
{
    uint32 i = 0;
    std::list<MapObject*>::const_iterator itr;
    range *= range;
    for (itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        if (MapObject* tmp = (*itr))
            if (tmp->GetDistance2dSquare(x, y) <= range)
	    {
                list.push_back(tmp);
		i++;
	    }
    return i;
}

uint32 Map::GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const
{
    float x, y;
    obj->GetPosition(x, y);
    return(GetObjectListInRange(x, y, range, list));
}

uint32 Map::GetObjectListInRange(float x, float y, float range, std::list<MapObject*>& list) const
{
  uint32 i = 0;
    for (int32 iy = -GRID_SIZE; iy <= GRID_SIZE; iy += GRID_SIZE)
        for (int32 ix = -GRID_SIZE; ix <= GRID_SIZE; ix += GRID_SIZE)
            if (MapGrid const* grid = GetGridAt(x + ix, y + iy))
	    {
	      i += grid->GetObjectListInRange(x, y, range, list);
	    }
    return i;
}

void Map::GetObjectList(float x, float y, std::list<GameObject*> &list) const
{
    for (int32 iy = -GRID_SIZE; iy <= GRID_SIZE; iy += GRID_SIZE)
        for (int32 ix = -GRID_SIZE; ix <= GRID_SIZE; ix += GRID_SIZE)
            if (MapGrid const* grid = GetGridAt(x + ix, y + iy))
                grid->GetObjectList(list);
}

void Map::GetObjectList(const GameObject *obj, std::list<GameObject*> &list) const
{
    float x, y;
    obj->GetPosition(x, y);

    for (int32 iy = -GRID_SIZE; iy <= GRID_SIZE; iy += GRID_SIZE)
        for (int32 ix = -GRID_SIZE; ix <= GRID_SIZE; ix += GRID_SIZE)
            if (MapGrid const* grid = GetGridAt(x + ix, y + iy))
                grid->GetObjectList(list);
}

void Map::GetAllObject(std::list<GameObject*> &list) const
{
    std::map<std::pair<float, float>, MapGrid*>::const_iterator itr;
    for (itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        itr->second->GetObjectList(list);
}

void Map::RegisterLua(lua_State* state)
{
    luabind::module(state) [
        luabind::class_<Map>("Map")
        .def("RemoveObject", &Map::RemoveObject)
        ];
}

ScoreMgr& Map::GetScoreMgr()
{
    return _scoreMgr;
}

ScoreMgr const& Map::GetScoreMgr() const
{
    return _scoreMgr;
}

void Map::SendScores(uint64 from)
{
    Packet data(SMSG_SEND_SCORE);
    _scoreMgr.WriteScores(data, from);
    BroadcastToAll(data);
}

void Map::BroadcastToAll(Packet const& pkt)
{
    std::map<std::pair<float, float>, MapGrid*>::iterator itr;
    for (itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        itr->second->BroadcastToGrid(pkt);
}

void Map::GetRandomStartPosition(float& x, float& y)
{
    bool ok;

    do
    {
        x = rand() % (_width - MAP_PRECISION);
        y = rand() % (_height - MAP_PRECISION);

        std::list<GameObject*> list;
        GetObjectList(x, y, list);
        try
        {
            ModelBox self = sModelMgr->GetModelBoxAtPos(x, y, 0.f, MODELID_PLAYER);
            std::list<GameObject*>::const_iterator it;
            for (it = list.begin(); it != list.end(); ++it)
            {
                ModelBox box = sModelMgr->GetModelBoxAtPos(*it);
                if (box.crossable == true)
                    continue;

                if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                    (self.max.y > box.min.y && self.min.y < box.max.y))
                {
                    ok = false;
                    break;
                }
                else
                    ok = true;
            }
        }
        catch (const std::exception&)
        {
            ok = false;
        }
    }
    while (!ok);
}

void Map::TeleportPlayer(Player* player, float x, float y)
{
    player->UpdatePosition(x, y, 0.0f);

    UpdateObjectGrid(player);

    GridUpdater(player, GRIDUPDATE_TELEPORT, UPDATE_FULL);
}

bool Map::IsFinish() const
{
    return _gameTimer == 0;
}

void Map::HandleGameFinish()
{
    Packet data(SMSG_GAME_FINISH, 0);
    BroadcastToAll(data);
}

uint32 Map::GetGameTimer() const
{
    return _gameTimer;
}

void Map::SaveToFile(std::string const& filename) const
{
    std::ofstream file;
    try
    {
        file.open(filename.c_str());
    }
    catch (std::exception const& e)
    {
        sLog->error("Error: %s", e.what());
        return;
    }

    file << _width << "," << _height << "," << _nextGuid << "," << _gameTimer << std::endl;


    std::map<uint64, Score*>::const_iterator itr = _scoreMgr.ScoreBegin();
    std::stringstream ss;
    uint32 count = 0;
    for (; itr != _scoreMgr.ScoreEnd(); ++itr)
        if (MapObject const* obj = GetObject(itr->first))
            if (obj->GetTypeId() == TYPEID_OBJECT)
            {
                Score const* sc = itr->second;
                ss << obj->GetGUID() << "," << sc->name << "," << sc->died << "," << sc->killed << "," << sc->bomb << "," << sc->wall << std::endl;
                ++count;
            }
    file << count << std::endl;
    file << ss.str();

    std::list<MapObject*> list;
    for (std::map<std::pair<float, float>, MapGrid*>::const_iterator itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        itr->second->AddObjectForUpdate(list);
    list.remove_if(ModelIdRemover(MODELID_BOMB));
    list.remove_if(TypeIdRemover(TYPEID_PLAYER));
    file << list.size() << std::endl;
    for (std::list<MapObject*>::const_iterator itr = list.begin(); itr != list.end(); ++itr)
        file << (*itr) << std::endl;

    file.close();
}

bool Map::TypeIdRemover::operator()(MapObject const* obj) const
{
    return obj->GetTypeId() == _id;
}

MapObject const* Map::GetObject(uint64 guid) const
{
    std::list<MapObject*> list;
    for (std::map<std::pair<float, float>, MapGrid*>::const_iterator itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        itr->second->AddObjectForUpdate(list);

    for (std::list<MapObject*>::const_iterator itr = list.begin(); itr != list.end(); ++itr)
        if ((*itr)->GetGUID() == guid)
            return (*itr);
    return NULL;
}

MapObject* Map::GetObject(uint64 guid)
{
    std::list<MapObject*> list;
    for (std::map<std::pair<float, float>, MapGrid*>::iterator itr = _mapGridMap.begin(); itr != _mapGridMap.end(); ++itr)
        itr->second->AddObjectForUpdate(list);

    for (std::list<MapObject*>::iterator itr = list.begin(); itr != list.end(); ++itr)
        if ((*itr)->GetGUID() == guid)
            return (*itr);
    return NULL;
}

Map* Map::LoadFromFile(std::string const& filename)
{
    std::ifstream file;
    file.open(filename.c_str());

    std::string line;
    if (!std::getline(file, line))
        throw std::logic_error("invalide map file");

    Map* newMap = NULL;

    {
        std::vector<std::string> s;
        split(line, ',', s);
        if (s.size() != 4)
            throw std::logic_error("invalide map file");

        newMap = new Map(to<uint32>(s[0]), to<uint32>(s[1]),
                to<uint32>(s[2]), to<uint32>(s[3]));
    }

    if (!std::getline(file, line))
        throw std::logic_error("invalide map file");
    newMap->LoadScore(to<uint32>(line), file);

    if (!std::getline(file, line))
        throw std::logic_error("invalide map file");

    uint32 count = to<uint32>(line);
    for (; count > 0; --count)
    {
        if (!std::getline(file, line))
            throw std::logic_error("invalide map file");

        std::vector<std::string> s;
        split(line, ',', s);
        if (s.size() != 9)
            throw std::logic_error("invalide map file");

        uint32 model = to<uint32>(s[0]);
        std::string name = s[1];
        float speed = to<float>(s[2]);
        float speedor = to<float>(s[3]);
        float posx = to<float>(s[4]);
        float posy = to<float>(s[5]);
        float posz = to<float>(s[6]);
        float orr = to<float>(s[7]);
        uint64 guid = to<uint64>(s[8]);

        Object* obj = new Object(guid, model, name);
        obj->SetSpeed(speed);
        obj->SetSpeedOr(speedor);
        obj->UpdatePosition(posx, posy, posz, orr);

        switch (model)
        {
            case MODELID_WALL:
                obj->InitializeAI("Scripts/wall.lua");
                break;
            case MODELID_BORDER:
                obj->InitializeAI("Scripts/border.lua");
                break;
            default:
                break;
        }

        newMap->AddObject(obj);
    }
    file.close();
    return newMap;
}

void Map::LoadScore(uint32 count, std::ifstream& stream)
{
    for (; count > 0; --count)
    {
        std::string line;
        if (!std::getline(stream, line))
            throw std::logic_error("invalide map file");

        std::vector<std::string> s;
        split(line, ',', s);
        if (s.size() != 6)
            throw std::logic_error("invalide map file");

        uint64 guid = to<uint64>(s[0]);
        Score* sc = new Score();
        sc->name = s[1];
        sc->died = to<uint32>(s[2]);
        sc->killed = to<uint32>(s[3]);
        sc->bomb = to<uint32>(s[4]);
        sc->wall = to<uint32>(s[5]);
        _scoreMgr.AddPlayer(guid, sc);
    }
}
