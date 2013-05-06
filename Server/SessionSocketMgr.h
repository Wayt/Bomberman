/*
** SessionSocketMgr.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 18:05:32 2013 maxime ginters
** Last update Mon May 06 18:33:04 2013 maxime ginters
*/

#ifndef SESSIONSOCKETMGR_H_
# define SESSIONSOCKETMGR_H_

#include <boost/asio.hpp>
#include "Shared.h"
#include "RunRunnable.hpp"
#include "SessionSocketAcceptor.h"

class SessionSocketMgr
{
public:
    SessionSocketMgr();

    boost::asio::io_service& GetIOService();

    bool Initialize(std::string const& addr, std::string const& port, uint8 netthread);
    void StartNetwork();
    void StopNetwork();
    void JoinNetwork();

    void HandleAccept(SessionSocket* new_sock, const boost::system::error_code& error);

private:
    boost::asio::io_service _io_service;
    SessionSocketAcceptor _acceptor;
    uint8 _NetThreadsCount;
    RunnablePool<boost::asio::io_service> _NetThreads;
};

#endif /* !SESSIONSOCKETMGR_H_ */
