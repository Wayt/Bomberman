/*
** Bomb.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:43:16 2013 maxime ginters
** Last update Wed May 29 15:15:21 2013 maxime ginters
*/

#include <iostream>
#include "Map.h"
#include "Bomb.h"

Bomb::Bomb(uint64 guid, MapObject* obj) :
    Object(guid, MODELID_BOMB, std::string("Bomb - ") + obj->GetName())
{
    SetOwner(obj);
    InitializeAI("Scripts/bomb.lua");
}

void Bomb::DoAction(uint32 id)
{
    switch (id)
    {
        case 1:
            HandleExplode();
            break;
        default:
            break;
    }
}

void Bomb::HandleExplode()
{
    std::cout << "BOUM" << std::endl;
    std::list<MapObject*> list;
    GetObjectListInRange(10.0f, list);

    std::list<MapObject*>::iterator itr;
    for (itr = list.begin(); itr != list.end(); ++itr)
        if (MapObject* obj = *itr)
            if (obj->IsInWorld())
                obj->HandleHit(this);

}
