/*
** SessionSocketMgr.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 18:05:32 2013 maxime ginters
** Last update Fri May 10 15:49:07 2013 maxime ginters
*/

#ifndef SESSIONSOCKETMGR_H_
# define SESSIONSOCKETMGR_H_

#include <boost/asio.hpp>
#include "Shared.h"
#include "RunRunnable.hpp"
#include "SessionSocketAcceptor.h"
#include "SessionSocket.h"
#include "Opcodes.h"

class SessionSocket;
class Server;

class SessionSocketMgr
{
public:
    SessionSocketMgr(Server* srv);

    boost::asio::io_service& GetIOService();

    bool Initialize(std::string const& addr, std::string const& port, uint8 netthread);
    void StartNetwork();
    void StopNetwork();
    void JoinNetwork();

    void HandleAccept(SessionSocket* new_sock, const boost::system::error_code& error);

    void RemoveNewSock(SessionSocket* sock);

    Server* GetServer() const;

private:
    boost::asio::io_service _io_service;
    SessionSocketAcceptor _acceptor;
    uint8 _NetThreadsCount;
    RunnablePool<boost::asio::io_service> _NetThreads;
    std::list<SessionSocket*> _NewSocks;
    Server* _server;
};

#endif /* !SESSIONSOCKETMGR_H_ */
