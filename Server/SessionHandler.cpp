/*
** SessionHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:42:46 2013 maxime ginters
** Last update Fri May 10 15:43:38 2013 maxime ginters
*/

#include "Session.h"

void Session::HandlePlayerName(Packet& recvData)
{
    std::string name;
    recvData >> name;

    std::cout << "Player name : " << name << std::endl;
}
