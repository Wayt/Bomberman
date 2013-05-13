/*
** SessionHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:42:46 2013 maxime ginters
** Last update Mon May 13 17:10:18 2013 maxime ginters
*/

#include "Session.h"

void Session::HandleLoginPlayer(Packet& recvData)
{
    std::string name;
    recvData >> name;

    std::cout << "Player name : " << name << std::endl;
    // Check nick availability

    _status = STATUS_AUTHED;

    Packet data(SMSG_LOGIN_RESPONSE, 1);
    data << uint8(LOGIN_RESPONSE_OK);
    SendPacket(data);
}
