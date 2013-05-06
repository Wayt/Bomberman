/*
** SessionSocket.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:18 2013 maxime ginters
** Last update Mon May 06 18:35:29 2013 maxime ginters
*/

#include "SessionSocket.h"
#include "Session.h"
#include "SessionSocketMgr.h"

SessionSocket::SessionSocket(boost::asio::io_service& io_service) :
    _socket(io_service), _session(NULL)
{}

tcp::socket& SessionSocket::socket()
{
    return _socket;
}

void SessionSocket::OnOpen()
{
    std::cout << "SessionSocket start" << std::endl;
}

