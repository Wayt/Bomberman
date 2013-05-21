/*
** Bomb.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:43:16 2013 maxime ginters
** Last update Sun May 19 15:46:15 2013 maxime ginters
*/

#include <iostream>
#include "Map.h"
#include "Bomb.h"

Bomb::Bomb(uint64 guid, MapObject* obj, uint32 mstimer) : MapObject(guid, MODELID_BOMB, TYPEID_OBJECT, std::string("Bomb - ") + obj->GetName()),
    _timer(mstimer), _bommed(false)
{
    SetOwner(obj);
}

void Bomb::Update(uint32 const diff)
{
    MapObject::Update(diff);

    if (_bommed)
        return;

    if (_timer <= diff)
    {
        HandleBoum();
    }
    else
        _timer -= diff;
}

void Bomb::HandleBoum()
{
    std::cout << "BOUM" << std::endl;
    std::list<MapObject*> objList;
    GetObjectListInRange(BOMB_RANGE, objList);

    for (std::list<MapObject*>::const_iterator itr = objList.begin(); itr != objList.end(); ++itr)
        std::cout << "BOUM ON : " << (*itr)->GetName() << std::endl;

    if (_map)
        _map->RemoveObject(this);
    delete this;
}
