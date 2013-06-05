/*
** Bomb.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:43:16 2013 maxime ginters
** Last update Thu Jun 06 01:07:33 2013 Aymeric Girault
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

class BombRangeMatch
{
    public:
        BombRangeMatch(float blockx, float blocky)
            : _blockx(blockx), _blocky(blocky)
        {
        }

        bool operator()(MapObject* obj) const
        {
	  if (obj->IsInWorld() && obj->IsAlive())
	    if ((obj->GetPositionX() > (_blockx - 2.5f) && obj->GetPositionX() < (_blockx + 2.5f)) ||
		(obj->GetPositionY() > (_blocky - 2.5f) && obj->GetPositionY() < (_blocky + 2.5f)))
	      return false;
	  return true;
	}

    private:
        float _blockx;
        float _blocky;
};

uint32 countWall(std::list<MapObject*> torm)
{
  std::list<MapObject*>::iterator itr;
  uint32 i = 0;

  for(itr = torm.begin(); itr != torm.end(); ++itr)
  {
    if ((*itr)->GetModelId() == MODELID_WALL || (*itr)->GetModelId() == MODELID_BORDER)
      i++;
  }
  return i;
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

    std::list<MapObject*> torm;
    _map->GetObjectListInRange(blockx, blocky, 2.5f, torm);
    uint32 nbWall = 0;
    /* X positif */
    for (uint32 i = 1; i <= GetBombRange() / 5.0f; i++) {
      if (_map->GetObjectListInRange(i * 5.0f + blockx, blocky, 2.5f, torm) > 0 && countWall(torm) > nbWall)
      {
	nbWall = countWall(torm);
	break;
      }
    }
    /* Y positif */
    for (uint32 i = 1; i <= GetBombRange() / 5.0f; i++) {
      if (_map->GetObjectListInRange(blockx, i * 5.0f + blocky, 2.5f, torm) > 0 && countWall(torm) > nbWall)
      {
	nbWall = countWall(torm);
	break;
      }
    }
    /* X negatif */
    for (uint32 i = 1; i <= GetBombRange() / 5.0f; i++) {
      if (_map->GetObjectListInRange(i * - 5.0f + blockx, blocky, 2.5f, torm) > 0 && countWall(torm) > nbWall)
      {
	nbWall = countWall(torm);
	break;
      }
    }
    /* Y negatif */
    for (uint32 i = 1; i <= GetBombRange() / 5.0f; i++) {
      if (_map->GetObjectListInRange(blockx, i * - 5.0f + blocky, 2.5f, torm) > 0 && countWall(torm) > nbWall)
      {
	nbWall = countWall(torm);
	break;
      }
    }
    std::list<MapObject*>::iterator itr;
    for (itr = torm.begin(); itr != torm.end(); ++itr)
      if (MapObject* obj = *itr)
      {
	obj->HandleHit(this);
      }
}

void Bomb::Despawn()
{
    if (MapObject* owner = _map->GetObject(_owner))
        owner->DecreasBombCount();

    Object::Despawn();
}

