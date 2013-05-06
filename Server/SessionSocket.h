/*
** SessionSocket.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:10 2013 maxime ginters
** Last update Mon May 06 19:24:38 2013 maxime ginters
*/

#ifndef SESSIONSOCKET_H_
# define SESSIONSOCKET_H_

#define SOCKET_BUFFER_SIZE 4096

#include <boost/asio.hpp>
#include "Shared.h"

class Session;

using boost::asio::ip::tcp;

class SessionSocket
{
public:
    SessionSocket(boost::asio::io_service& io_service);

    tcp::socket& socket();

    void OnOpen();

    void HandleInput(boost::system::error_code const& error, std::size_t reicvSize);
private:
    void _RegisterRead();
    tcp::socket _socket;
    Session* _session;
    char buffer[SOCKET_BUFFER_SIZE];
};

#endif /* !SESSIONSOCKET_H_ */
