/*
** MapObject.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:38:06 2013 maxime ginters
** Last update Wed Jun 05 16:41:36 2013 maxime ginters
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

    virtual void SetGrid(MapGrid* grid);
    void SetMap(Map* map);
    TypeId GetTypeId() const;

    void BuildObjectCreateForPlayer(Packet& data) const;

    MotionMaster const* GetMotionMaster() const;
    MotionMaster* GetMotionMaster();

    virtual void SendPacket(Packet const& data);

    Map* GetMap();
    MapGrid* GetGrid();

    virtual void Update(uint32 const diff);

    void HandlePositionChange();

    uint64 GetOwner();
    void SetOwner(uint64 guid);

    void GetObjectListInRange(float range, std::list<MapObject*>& list) const;
    std::list<MapObject*> GetObjectListInRange(float range);

    virtual ObjectAI* GetAI();

    virtual void HandleHit(MapObject* obj);

    static void RegisterLua(lua_State* state);

protected:
    bool _isInWorld;
    MapGrid* _currGrid;
    std::string _name;
    TypeId _typeId;
    MotionMaster* _motionMaster;
    uint64 _owner;
};

std::ofstream& operator<<(std::ofstream& stream, MapObject const* obj);
std::ofstream& operator<<(std::ofstream& stream, MapObject const& obj);

#endif /* !MAPOBJECT_H_ */
