/*
** Bomb.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:43:16 2013 maxime ginters
** Last update Fri May 24 20:22:53 2013 maxime ginters
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
}
