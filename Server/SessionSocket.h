/*
** SessionSocket.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 17:26:10 2013 maxime ginters
** Last update Mon May 06 18:35:36 2013 maxime ginters
*/

#ifndef SESSIONSOCKET_H_
# define SESSIONSOCKET_H_

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
private:
    tcp::socket _socket;
    Session* _session;
};

#endif /* !SESSIONSOCKET_H_ */
