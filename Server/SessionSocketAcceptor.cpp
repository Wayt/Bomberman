/*
** SessionSocketAcceptor.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:32:40 2013 maxime ginters
** Last update Mon May 06 18:35:03 2013 maxime ginters
*/

#include "SessionSocketAcceptor.h"
#include "SessionSocketMgr.h"

SessionSocketAcceptor::SessionSocketAcceptor(SessionSocketMgr* mgr) :
    _socketMgr(mgr), _acceptor(mgr->GetIOService())
{
}

bool SessionSocketAcceptor::Initialize(std::string const& addr, std::string const& port)
{
    try
    {
        tcp::resolver resolver(_socketMgr->GetIOService());
        tcp::resolver::query query(addr, port);
        tcp::endpoint endpoint = *resolver.resolve(query);
        _acceptor.open(endpoint.protocol());
        _acceptor.set_option(tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint);
        _acceptor.listen();
    }
    catch (boost::system::system_error& e)
    {
        sLog->error("Error: %s", e.what());
        return false;
    }

    RegisterAccept();
    return true;
}

void SessionSocketAcceptor::RegisterAccept()
{
    SessionSocket* new_sock = new SessionSocket(_socketMgr->GetIOService());
    _acceptor.async_accept(new_sock->socket(),
            boost::bind(&SessionSocketMgr::HandleAccept, _socketMgr, new_sock,
                boost::asio::placeholders::error));

}


