/*
** MapObject.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 17:38:06 2013 maxime ginters
** Last update Fri Jun 07 00:44:07 2013 maxime ginters
*/

#ifndef MAPOBJECT_H_
# define MAPOBJECT_H_

#include "Shared.h"
#include "Packet.hpp"
#include "GameObject.h"
#include "MotionMaster.hpp"
#include "Map.h"

#define TIME_TO_RESPAWN 15000

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

    void SetSpeed(float speed);

    void BuildObjectCreateForPlayer(Packet& data) const;

    MotionMaster const* GetMotionMaster() const;
    MotionMaster* GetMotionMaster();

    virtual void SendPacket(Packet const& data);

    Map* GetMap();
    Map const* GetMap() const;
    MapGrid* GetGrid();

    virtual void Update(uint32 const diff);

    void HandlePositionChange();

    uint64 GetOwner();
    void SetOwner(uint64 guid);

    void GetObjectListInRange(float range, std::list<MapObject*>& list) const;
    std::list<MapObject*> GetObjectListInRange(float range);

    virtual ObjectAI* GetAI();

    virtual bool HandleHit(MapObject* obj);

    static void RegisterLua(lua_State* state);

    void DropBombIfPossible();
    void DecreasBombCount();

    virtual void HandleRespawn();

    void AddMaxBombCount(uint32 value);

    virtual void RandomTeleport();

    float GetBombRange() const;
    void IncrBombRange(float value);

    void Kill(MapObject* by);

    void GetBoxCenter(float& x, float& y) const;
    bool IsPositionSafe() const;

    virtual void HandleBombBoum();


    bool CanBeHitByAtPos(MapObject* bomb, float sx, float sy, std::list<MapObject*> const& list) const;
protected:
    bool CanBeHitBy(MapObject* bomb, std::list<MapObject*> const& list) const;

    bool _isInWorld;
    MapGrid* _currGrid;
    TypeId _typeId;
    MotionMaster* _motionMaster;
    uint64 _owner;

    uint32 _maxBomb;
    uint32 _currBomb;
    float _bombPower;
    uint32 _telTimer;

    class WallPositionCheck
    {
    public:
        WallPositionCheck(float x, float y) :
            _posx(x), _posy(y)
        {}

        bool operator()(MapObject const* obj)
        {
            if (FuzzyCompare(_posx, obj->GetPositionX()) && FuzzyCompare(_posy, obj->GetPositionY()))
                return true;
            return false;
        }
    private:
        float _posx;
        float _posy;
    };
};

std::ofstream& operator<<(std::ofstream& stream, MapObject const* obj);
std::ofstream& operator<<(std::ofstream& stream, MapObject const& obj);

#endif /* !MAPOBJECT_H_ */
