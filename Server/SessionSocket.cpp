/*
** SessionSocket.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:18 2013 maxime ginters
** Last update Mon May 06 19:24:39 2013 maxime ginters
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

void SessionSocket::HandleInput(boost::system::error_code const& error, std::size_t bytes_transferred)
{
    if (error)
    {
        std::cout << "Error: " << error.message() << std::endl;
        _socket.close();
        return;
    }
    (void)bytes_transferred;
    (void)_session;
    std::cout << "HandleInput" << std::endl;
    _RegisterRead();
}

void SessionSocket::_RegisterRead()
{
    _socket.async_read_some(boost::asio::buffer(buffer, SOCKET_BUFFER_SIZE),
            boost::bind(&SessionSocket::HandleInput, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

