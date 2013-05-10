/*
** SessionSocket.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:18 2013 maxime ginters
** Last update Fri May 10 16:10:49 2013 maxime ginters
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

    (void)bytes_transferred;
    (void)_session;
    std::cout << "HandleInput : ";
    std::cout.write(buffer, bytes_transferred);
    std::cout << std::endl;

    _session->QueuePacket(new Packet(buffer, bytes_transferred));
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

