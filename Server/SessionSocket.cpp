/*
** SessionSocket.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:18 2013 maxime ginters
** Last update Fri May 10 23:05:11 2013 maxime ginters
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

bool SessionSocket::IsClosed() const
{
    return !_socket.is_open();
}

void SessionSocket::OnOpen()
{
    std::cout << "SessionSocket start" << std::endl;
    _session = new Session(this, _sockMgr->GetServer());
    _RegisterRead();
}

void SessionSocket::OnClose()
{
    std::cout << "SessionSocket close" << std::endl;
}

void SessionSocket::Close()
{
    OnClose();
    _socket.close();
}
void SessionSocket::HandleInput(boost::system::error_code const& error, std::size_t bytes_transferred)
{
    if (error)
    {
        std::cout << "Error: " << error.message() << std::endl;
        if (_session)
            _session->Close();
        return;
    }

    if (!_session)
        return;

    header[bytes_transferred] = 0;
    uint16 size = to<uint16>(header);
    char buff[size];

    boost::system::error_code ignored_ec;
    read(_socket, boost::asio::buffer(buff, size), ignored_ec);

    _session->QueuePacket(new Packet(buff, size));
    _RegisterRead();
}

void SessionSocket::SendPacket(Packet const* packet)
{
    _socket.write_some(boost::asio::buffer(packet->content(), packet->size()));
}

void SessionSocket::_RegisterRead()
{
    async_read(_socket, boost::asio::buffer(header, PACKET_HEADER_SIZE),
            boost::bind(&SessionSocket::HandleInput, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

