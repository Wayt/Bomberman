/*
** Map.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:31:52 2013 maxime ginters
** Last update Thu Jun 06 00:10:54 2013 maxime ginters
*/

#ifndef MAP_H_
# define MAP_H_

#include <map>
#include "Shared.h"
#include "Packet.hpp"
#include "luabind.h"
#include "ScoreMgr.h"
#include "GameObject.h"

#define MAP_PRECISION 5
#define GRID_SIZE (MAP_PRECISION * 10)

class MapObject;
class Player;

enum GridUpdaterActions
{
    GRIDUPDATE_ACTIVE   = 0x0001,
    GRIDUPDATE_SENDOBJ  = 0x0002,
    GRIDUPDATE_MOVEFLAGS= 0x0004,
    GRIDUPDATE_DELOBJ   = 0x0008,
    GRIDUPDATE_KILLED   = 0x0010,
    GRIDUPDATE_RESPAWN  = 0x0020,
    GRIDUPDATE_TELEPORT = 0x0040,
    GRIDUPDATE_SPEED    = 0x0080,
    GRIDUPDATE_BOUM     = 0x0100,
};

enum GridUpdaterFlags
{
    UPDATE_UP           = 0x01,
    UPDATE_DOWN         = 0x02,
    UPDATE_LEFT         = 0x04,
    UPDATE_RIGHT        = 0x08,
    UPDATE_CURRENT      = 0x10,
    UPDATE_FULL         = (UPDATE_UP | UPDATE_DOWN | \
                          UPDATE_LEFT | UPDATE_RIGHT | \
                          UPDATE_CURRENT),
};

#define GRID_UPDATE_COUNT 9

struct GridUpdateOrder
{
    float x;
    float y;
    uint8 flags;
};

class MapGrid
{
public:
    MapGrid();

    bool IsActive() const;
    void AddObject(MapObject* obj);
    void RemoveObject(MapObject* obj);

    void UpdateForMapObject(MapObject* player, uint16 action);
    void GridUpdateActive(MapObject *obj);
    void GridUpdateSendObject(MapObject *obj);
    void GridUpdateMoveFlags(MapObject *obj);
    void GridUpdateDelObj(MapObject *obj);
    void GridUpdateKilled(MapObject *obj);
    void GridUpdateRespawn(MapObject *obj);
    void GridUpdateTeleport(MapObject *obj);
    void GridUpdateSpeed(MapObject *obj);
    void GridUpdateBoum(MapObject *obj);
    void BroadcastToGrid(Packet const& pkt, MapObject* except = NULL);

    void AddObjectForUpdate(std::list<MapObject*>& list) const;
    void GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const;
    void GetObjectListInRange(float x, float y, float range, std::list<MapObject*>& list) const;
    void GetObjectList(std::list<GameObject*> &list) const;
private:
    std::list<MapObject*> _objectList;
    bool _isActive;

    struct GridUpdaterFunction
    {
        uint16 flag;
        void (MapGrid::*update)(MapObject*);
    };
};

class Map
{
public:
    explicit Map(uint32 width, uint32 height, uint32 nguid = 1, uint32 time = 600000);

    static Map* CreateNewRandomMap(const uint32 width, const uint32 height, float complexity, float density);
    static Map* LoadFromFile(std::string const& filename);

    void AddObject(MapObject* obj);
    void RemoveObject(MapObject* obj);

    uint8 BuildGridUpdaterFlags(MapGrid* old, MapGrid* newGrid) const;
    void GridUpdater(MapObject* obj, uint16 action, uint8 updateFlags);

    uint64 MakeNewGuid();

    void GetWidthAndHeight(uint32& width, uint32& height) const;
    uint32 GetWidth() const;
    uint32 GetHeight() const;

    MapObject const* GetObject(uint64 guid) const;
    MapObject* GetObject(uint64 guid);

    void Update(uint32 const diff);

    void UpdateObjectGrid(MapObject* obj);

    void GetObjectListInRange(MapObject const* obj, float range, std::list<MapObject*>& list) const;
    void GetObjectListInRange(float x, float y, float range, std::list<MapObject*>& list) const;

    void GetObjectList(float x, float y, std::list<GameObject*> &list, uint32 &w, uint32 &h) const;
    void GetObjectList(const GameObject *obj, std::list<GameObject*> &list) const;

    void GetAllObject(std::list<GameObject*> &list) const;

    ScoreMgr& GetScoreMgr();
    ScoreMgr const& GetScoreMgr() const;
    void SendScores(uint64 from = 0);

    void BroadcastToAll(Packet const& pkt);

    void GetRandomStartPosition(float& x, float& y);

    void TeleportPlayer(Player* player, float x, float y);

    uint32 GetGameTimer() const;
    bool IsFinish() const;
    void HandleGameFinish();

    static void RegisterLua(lua_State* state);

    void SaveToFile(std::string const& filename) const;
    void LoadScore(uint32 count, std::ifstream& stream);

private:
    bool _GetGridXY(MapGrid* grid, float& x, float& y) const;
    MapGrid* GetGridAt(float x, float y);
    MapGrid const* GetGridAt(float x, float y) const;

    std::map<std::pair<float, float>, MapGrid*> _mapGridMap;
    uint64 _nextGuid;
    uint32 _width;
    uint32 _height;
    std::list<MapObject*> _removeList;
    ScoreMgr _scoreMgr;
    uint32 _gameTimer;

    class ModelIdRemover
    {
    public:
        ModelIdRemover(uint32 id) : _id(id) {}
        bool operator()(GameObject const* obj) const
        {
            return obj->GetModelId() == _id;
        }
    private:
        uint32 _id;
    };
    class TypeIdRemover
    {
    public:
        TypeIdRemover(uint32 id) : _id(id) {}
        bool operator()(MapObject const* obj) const;
    private:
        uint32 _id;
    };
};

#endif /* !MAP_H_ */
