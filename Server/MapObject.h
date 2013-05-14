/*
** MapObject.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:38:06 2013 maxime ginters
** Last update Tue May 14 17:32:22 2013 maxime ginters
*/

#ifndef MAPOBJECT_H_
# define MAPOBJECT_H_

#include "Shared.h"
#include "Packet.hpp"
#include "Position.h"

class MapGrid;
class Map;

enum ModelIds
{
    MODELID_PLAYER  = 0,
    MODELID_WALL    = 1,
    MODELID_BOMB    = 2
};

enum TypeId
{
    TYPEID_PLAYER   = 0,
    TYPEID_OBJECT   = 1,
};

class MapObject : public Position
{
public:
    explicit MapObject(uint64 guid, uint32 modelId, TypeId type, std::string const& name);

    void SetInWorld(bool in_world = true);
    bool IsInWorld() const;
    uint32 GetModelId() const;
    std::string const& GetName() const;

    virtual void SetGrid(MapGrid* grid);
    void SetMap(Map* map);
    TypeId GetTypeId() const;

    void BuildObjectCreateForPlayer(Packet& data) const;
    uint64 GetGUID() const;
protected:
    uint32 _modelId;
    bool _isInWorld;
    MapGrid* _currGrid;
    std::string _name;
    Map* _map;
    TypeId _typeId;
    uint64 const _guid;
};

#endif /* !MAPOBJECT_H_ */
