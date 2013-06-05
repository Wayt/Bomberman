/*
** Range.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 19:27:12 2013 vincent leroy
** Last update Wed Jun 05 19:36:30 2013 vincent leroy
*/

#include "Range.h"

Range::Range(uint64 guid) :
    Object(guid, MODELID_RANGE, "Range")
{
    InitializeAI("Scripts/range.lua");
}

Range::~Range()
{
}
