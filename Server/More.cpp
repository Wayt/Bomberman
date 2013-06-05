/*
** More.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 19:33:48 2013 vincent leroy
** Last update Wed Jun 05 19:35:28 2013 vincent leroy
*/

#include "More.h"

More::More(uint64 guid) :
    Object(guid, MODELID_MORE, "More")
{
    InitializeAI("Scripts/more.lua");
}

More::~More()
{
}
