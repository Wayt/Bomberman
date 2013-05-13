/*
** Map.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:31:52 2013 maxime ginters
** Last update Mon May 13 18:31:27 2013 maxime ginters
*/

#ifndef MAP_H_
# define MAP_H_

#include <map>
#include "Shared.h"
#include "MapObject.h"

#define GRID_SIZE 50
#define MAP_PRECISION 5

class MapGrid
{
public:
    MapGrid();

    bool IsLoaded() const;
    void AddObject(MapObject* obj);
    void RemoveObject(MapObject* obj);
private:
    std::list<MapObject*> _objectList;
    bool _isLoaded;
};

class Map
{
public:
    explicit Map(uint32 width, uint32 height);

    static Map* CreateNewRandomMap(const uint32 width, const uint32 height, float complexity, float density);

    void AddObject(MapObject* obj);

private:
    MapGrid* GetGridAt(float x, float y);
    std::map<std::pair<float, float>, MapGrid*> _mapGridMap;
};

#endif /* !MAP_H_ */
