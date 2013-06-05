/*
** Bomb.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:43:16 2013 maxime ginters
** Last update Thu Jun 06 00:18:40 2013 maxime ginters
*/

#include <iostream>
#include <cmath>
#include "Map.h"
#include "Bomb.h"

Bomb::Bomb(uint64 guid, MapObject* obj) :
    Object(guid, MODELID_BOMB, std::string("Bomb - ") + obj->GetName())
{
    SetOwner(obj->GetGUID());
    InitializeAI("Scripts/bomb.lua");
    _bombPower = obj->GetBombRange();
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
    float x, y;
    GetPosition(x, y);
    x += 2.5f;
    y += 2.5f;

    uint32 coefx = (uint32)x / 5;
    float blockx = 5 * coefx;

    uint32 coefy = (uint32)y / 5;
    float blocky = 5 * coefy;

    _map->GridUpdater(this, GRIDUPDATE_BOUM, UPDATE_FULL);

    float range = std::sqrt((2.5f * 2.5f) + (_bombPower * _bombPower));
    std::list<MapObject*> list;
    _map->GetObjectListInRange(blockx, blocky, range, list);

    std::list<MapObject*>::iterator itr;
    for (itr = list.begin(); itr != list.end(); ++itr)
        if (MapObject* obj = *itr)
            if (obj->IsInWorld() && obj->IsAlive())
                if ((obj->GetPositionX() > (blockx - 2.5f) && obj->GetPositionX() < (blockx + 2.5f)) ||
                        (obj->GetPositionY() > (blocky - 2.5f) && obj->GetPositionY() < (blocky + 2.5f)))
                    obj->HandleHit(this);

}

void Bomb::Despawn()
{
    if (MapObject* owner = _map->GetObject(_owner))
        owner->DecreasBombCount();

    Object::Despawn();
}

