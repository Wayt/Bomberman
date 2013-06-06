/*
** Object.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:55:11 2013 maxime ginters
** Last update Fri Jun 07 01:33:53 2013 maxime ginters
*/

#ifndef OBJECT_H_
# define OBJECT_H_

#include "MapObject.h"

class ObjectAI;
struct lua_State;

class Object : public MapObject
{
public:
    Object(uint64 guid, uint32 modelId, std::string const& name);
    virtual ~Object();

    ObjectAI* GetAI();

    bool InitializeAI(std::string const& filename);
    bool ReloadAI();

    virtual void Update(uint32 const diff);

    virtual void Despawn();

    static void RegisterLua(lua_State* state);

    virtual void DoAction(uint32 id);

    bool HandleHit(MapObject* obj);

    void SpawnBonus();

    void HandleCross(MapObject* by);

    void CheckBonusCross(float range);

    void HandleRespawn();

    void MovePoint(float x, float y);
    void MovePoint(MapObject const* to);

    void HandlePathGenerated(std::list<point> const& path);
    void HandleFailToCreatePath();
    void HandleFinishMovePoint();

    MapObject const* FindNearestPlayer() const;
    bool MoveToSafePosition();

    void HandleBombBoum();

    bool HasPlayerInRange(float range) const;

private:
    ObjectAI* _AI;


};

#endif /* !OBJECT_H_ */
