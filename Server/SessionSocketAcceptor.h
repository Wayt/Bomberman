/*
** SessionSocketAcceptor.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:32:40 2013 maxime ginters
** Last update Mon May 06 18:30:57 2013 maxime ginters
*/

#ifndef SESSIONSOCKETACCEPTOR_H_
# define SESSIONSOCKETACCEPTOR_H_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Shared.h"
#include "SessionSocket.h"

class SessionSocketMgr;

using boost::asio::ip::tcp;

class SessionSocketAcceptor
{
public:
    SessionSocketAcceptor(SessionSocketMgr* mgr);

    bool Initialize(std::string const& addr, std::string const& port);

    void RegisterAccept();
    void HandleAccept(SessionSocket* new_sock, const boost::system::error_code& error);

private:
    SessionSocketMgr* _socketMgr;
    boost::asio::ip::tcp::acceptor _acceptor;
};

#endif /* !SESSIONSOCKETACCEPTOR_H_ */
