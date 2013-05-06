/*
** SessionSocketAcceptor.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:32:40 2013 maxime ginters
** Last update Mon May 06 17:42:30 2013 maxime ginters
*/

#include "SessionSocketAcceptor.h"

SessionSocketAcceptor::SessionSocketAcceptor(boost::asio::io_service& io_service) :
    _io_service(io_service), _acceptor(_io_service)
{
}

bool SessionSocketAcceptor::Initialize(std::string const& addr, std::string const& port)
{
    try
    {
        tcp::resolver resolver(_io_service);
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

    SessionSocket* new_sock = new SessionSocket(_io_service);
    _acceptor.async_accept(new_sock->socket(),
            boost::bind(&SessionSocketAcceptor::HandleAccept, this, new_sock,
                boost::asio::placeholders::error));
    return true;
}

boost::asio::io_service& SessionSocketAcceptor::getIOService()
{
    return _io_service;
}

void SessionSocketAcceptor::HandleAccept(SessionSocket* new_sock, const boost::system::error_code& error)
{
    if (!error)
    {
        new_sock->start();
    }
    else
    {
        delete new_sock;
    }

    new_sock = new SessionSocket(_io_service);
    _acceptor.async_accept(new_sock->socket(),
            boost::bind(&SessionSocketAcceptor::HandleAccept, this, new_sock,
                boost::asio::placeholders::error));
}
