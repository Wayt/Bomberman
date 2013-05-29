/*
** MapObject.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:38:06 2013 maxime ginters
** Last update Wed May 29 15:30:31 2013 maxime ginters
*/

#ifndef MAPOBJECT_H_
# define MAPOBJECT_H_

#include "Shared.h"
#include "Packet.hpp"
#include "GameObject.h"
#include "MotionMaster.hpp"
#include "Map.h"

class MapGrid;
class ObjectAI;

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

class MapObject : public GameObject
{
public:
    explicit MapObject(uint64 guid, uint32 modelId, TypeId type, std::string const& name);
    virtual ~MapObject();

    void SetInWorld(bool in_world = true);
    bool IsInWorld() const;
    uint32 GetModelId() const;

    virtual void SetGrid(MapGrid* grid);
    void SetMap(Map* map);
    TypeId GetTypeId() const;

    void BuildObjectCreateForPlayer(Packet& data) const;
    uint64 GetGUID() const;

    MotionMaster const* GetMotionMaster() const;
    MotionMaster* GetMotionMaster();

    virtual void SendPacket(Packet const& data);

    Map* GetMap();
    MapGrid* GetGrid();

    virtual void Update(uint32 const diff);

    void HandlePositionChange();

    MapObject* GetOwner();
    void SetOwner(MapObject* obj);

    void GetObjectListInRange(float range, std::list<MapObject*>& list) const;
    std::list<MapObject*> GetObjectListInRange(float range);

    virtual ObjectAI* GetAI();

    virtual void HandleHit(MapObject* obj);

protected:
    uint32 _modelId;
    bool _isInWorld;
    MapGrid* _currGrid;
    std::string _name;
    TypeId _typeId;
    uint64 const _guid;
    MotionMaster* _motionMaster;
    MapObject* _owner;
};

#endif /* !MAPOBJECT_H_ */
