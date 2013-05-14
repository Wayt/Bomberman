/*
** Map.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:31:52 2013 maxime ginters
** Last update Tue May 14 17:06:59 2013 maxime ginters
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
    GRIDUPDATE_SENDOBJ  = 0x0002
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

    void UpdateForPlayer(Player* player, uint16 action);
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

    uint8 BuildGridUpdaterFlags(MapGrid* old, MapGrid* newGrid) const;
    void GridUpdater(Player* player, uint16 action, uint8 updateFlags);

    uint64 MakeNewGuid();

private:
    bool _GetGridXY(MapGrid* grid, float& x, float& y) const;
    MapGrid* GetGridAt(float x, float y);

    std::map<std::pair<float, float>, MapGrid*> _mapGridMap;
    uint64 _nextGuid;
};

#endif /* !MAP_H_ */
