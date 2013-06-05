/*
** Speed.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 18:36:15 2013 vincent leroy
** Last update Wed Jun 05 19:17:57 2013 vincent leroy
*/

#include "Speed.h"

Speed::Speed(uint64 guid) :
    Object(guid, MODELID_SPEED, "Speed")
{
    InitializeAI("Scripts/speed.lua");
}

Speed::~Speed()
{
}
