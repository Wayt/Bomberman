/*
** Map.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:31:52 2013 maxime ginters
** Last update Fri May 17 16:15:01 2013 maxime ginters
*/

#ifndef MAP_H_
# define MAP_H_

#include <map>
#include "Shared.h"
#include "MapObject.h"
#include "Player.h"

#define MAP_PRECISION 5
#define GRID_SIZE (MAP_PRECISION * 10)

enum GridUpdaterActions
{
    GRIDUPDATE_ACTIVE   = 0x0001,
    GRIDUPDATE_SENDOBJ  = 0x0002,
    GRIDUPDATE_MOVEFLAGS= 0x0004,
    GRIDUPDATE_DELOBJ   = 0x0008,
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
    float y;
    float x;
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
    void BroadcastToGrid(Packet& pkt, MapObject* except = NULL);

    void Update(uint32 const diff);
private:
    std::list<MapObject*> _objectList;
    bool _isActive;
};

class Map
{
public:
    explicit Map(uint32 width, uint32 height);

    static Map* CreateNewRandomMap(const uint32 width, const uint32 height, float complexity, float density);

    void AddObject(MapObject* obj);
    void RemoveObject(MapObject* obj);

    uint8 BuildGridUpdaterFlags(MapGrid* old, MapGrid* newGrid) const;
    void GridUpdater(MapObject* obj, uint16 action, uint8 updateFlags);

    uint64 MakeNewGuid();

    void GetWidthAndHeight(uint32& width, uint32& height) const;

    void Update(uint32 const diff);

private:
    bool _GetGridXY(MapGrid* grid, float& x, float& y) const;
    MapGrid* GetGridAt(float x, float y);

    std::map<std::pair<float, float>, MapGrid*> _mapGridMap;
    uint64 _nextGuid;
    uint32 _width;
    uint32 _height;
};

#endif /* !MAP_H_ */
