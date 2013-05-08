/*
** SessionSocket.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:18 2013 maxime ginters
** Last update Wed May 08 17:51:32 2013 maxime ginters
*/

#include "SessionSocket.h"
#include "Session.h"
#include "SessionSocketMgr.h"

SessionSocket::SessionSocket(SessionSocketMgr* sockMgr) :
    _socket(sockMgr->GetIOService()), _session(NULL), _sockMgr(sockMgr)
{}

tcp::socket& SessionSocket::socket()
{
    return _socket;
}

void SessionSocket::OnOpen()
{
    std::cout << "SessionSocket start" << std::endl;
    _RegisterRead();
}

void SessionSocket::OnClose()
{
    if (_session)
    {

    }
    else
        _sockMgr->RemoveNewSock(this);
}

void SessionSocket::HandleInput(boost::system::error_code const& error, std::size_t bytes_transferred)
{
    if (error)
    {
        std::cout << "Error: " << error.message() << std::endl;
        OnClose();
        _socket.close();
        delete this;
        return;
    }
    (void)bytes_transferred;
    (void)_session;
    std::cout << "HandleInput : ";
    std::cout.write(buffer, bytes_transferred);
    std::cout << std::endl;

    Packet data(SMSG_TEST, 4);
    data << uint32(42);
    SendPacket(&data);
    _RegisterRead();
}

void SessionSocket::SendPacket(Packet const* packet)
{
    const uint8* data = packet->content();
    size_t size = packet->size();
    for (size_t i = 0; i < size; ++i)
        printf("%x - ", data[i]);
    printf("\n");
    fflush(stdout);
    _socket.write_some(boost::asio::buffer(packet->content(), packet->size()));
}

void SessionSocket::_RegisterRead()
{
    _socket.async_read_some(boost::asio::buffer(buffer, SOCKET_BUFFER_SIZE),
            boost::bind(&SessionSocket::HandleInput, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

