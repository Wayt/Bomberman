/*
** SessionSocket.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:10 2013 maxime ginters
** Last update Fri May 10 16:02:57 2013 maxime ginters
*/

#ifndef SESSIONSOCKET_H_
# define SESSIONSOCKET_H_

#define SOCKET_BUFFER_SIZE 4096

#include <boost/asio.hpp>
#include "Shared.h"
#include "Packet.hpp"

class Session;
class SessionSocketMgr;

using boost::asio::ip::tcp;

class SessionSocket
{
public:
    SessionSocket(SessionSocketMgr* sockMgr);

    tcp::socket& socket();
    bool IsClosed() const;

    void OnOpen();
    void OnClose();

    void Close();

    void HandleInput(boost::system::error_code const& error, std::size_t reicvSize);

    void SendPacket(Packet const* packet);
private:
    void _RegisterRead();
    tcp::socket _socket;
    Session* _session;
    char buffer[SOCKET_BUFFER_SIZE];
    SessionSocketMgr* _sockMgr;
};

#endif /* !SESSIONSOCKET_H_ */
