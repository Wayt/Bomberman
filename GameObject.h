/*
** GameObject.h for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon May 27 18:26:54 2013 vincent leroy
** Last update Wed Jun 05 23:50:39 2013 maxime ginters
*/

#ifndef GAMEOBJECT_H_
# define GAMEOBJECT_H_

#include <list>
#include "Position.h"

class Map;
class Client;

enum ModelIds
{
    MODELID_PLAYER      = 0,
    MODELID_WALL        = 1,
    MODELID_BOMB        = 2,
    MODELID_BORDER      = 3,
    MODELID_SPEED       = 4,
    MODELID_RANGE       = 5,
    MODELID_MORE        = 6,
    MODELID_TELEPORT    = 7
};

class GameObject : public Position
{
public:
    GameObject(uint64 guid, uint32 modelId, const std::string &name);
    virtual ~GameObject();

    uint64 GetGUID() const;

    uint32 GetMovementFlags() const;
    void SetMovementFlags(uint32 flags);
    bool AddMovementFlag(uint32 flag);
    bool RemoveMovementFlag(uint32 flag);
    bool UpdateMovementFlag(uint32 flag, bool add);
    bool HasMovementFlag(uint32 flag) const;

    virtual void SetSpeed(float speed);
    float GetSpeed() const;
    void SetSpeedOr(float speed_or);
    float GetSpeedOr() const;

    uint32 GetModelId() const;
    std::string const& GetName() const;

    virtual void SetMap(Map *map);
    void SetClient(Client *client);
    Map* GetMap();
    Client* GetClient();

    void GetVisibleObject(std::list< GameObject*> &list) const;

    bool IsAlive() const;
    void SetAlive(bool alive);
    void UpdateRespawnTime(uint32 const diff);
    virtual void HandleRespawn();
    void SetRespawnTime(uint32 time);
    uint32 GetRespawnTime() const;
    void SetKilledBy(std::string const& by);
    std::string const& GetLastKiller() const;
    void SetKillerGUID(uint64 guid);
    uint64 GetLastKillerGUID() const;

protected:
    uint32 _modelId;
    std::string _name;
    float _speed;
    float _speed_or;
    uint32 _movementFlags;
    Map *_map;
    Client *_client;
    bool _alive;
    uint32 _respawnTime;
    std::string _lastKiller;
    uint64 _guid;
    uint64 _lastKillerGUID;
};

#endif /* !GAMEOBJECT_H_ */
