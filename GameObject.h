/*
** GameObject.h for Bomberman in /home/leroy_v/github/Bomberman
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon May 27 18:26:54 2013 vincent leroy
** Last update Mon May 27 19:24:20 2013 vincent leroy
*/

#ifndef GAMEOBJECT_H_
# define GAMEOBJECT_H_

#include <list>

#include "Position.h"

class Map;
class Client;

class GameObject : public Position
{
public:
    GameObject(uint32 modelId, const std::string &name);
    virtual ~GameObject();

    uint32 GetMovementFlags() const;
    void SetMovementFlags(uint32 flags);
    bool AddMovementFlag(uint32 flag);
    bool RemoveMovementFlag(uint32 flag);
    bool UpdateMovementFlag(uint32 flag, bool add);
    bool HasMovementFlag(uint32 flag) const;

    void SetSpeed(float speed);
    float GetSpeed() const;
    void SetSpeedOr(float speed_or);
    float GetSpeedOr() const;

    virtual void SetMap(Map *map);
    void SetClient(Client *client);
    Map* GetMap();
    Client* GetClient();

    void GetVisibleObject(std::list<const GameObject*> &list) const;

private:
    uint32 _modelId;
    std::string _name;
    float _speed;
    float _speed_or;
    uint32 _movementFlags;
    Map *_map;
    Client *_client;
};

#endif /* !GAMEOBJECT_H_ */
