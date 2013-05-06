/*
** Session.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 15:52:15 2013 maxime ginters
** Last update Mon May 06 17:37:55 2013 maxime ginters
*/

#include <iostream>
#include "Session.h"

Session::Session(SessionSocket* sock) :
    _socket(sock)
{}

SessionSocket* Session::GetSessionSocket()
{
    return _socket;
}

