/*
** SessionSocketMgr.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 18:05:32 2013 maxime ginters
** Last update Mon May 06 18:35:45 2013 maxime ginters
*/

#include "SessionSocketMgr.h"

SessionSocketMgr::SessionSocketMgr() : _io_service(),
    _acceptor(this), _NetThreadsCount(1), _NetThreads()
{}

boost::asio::io_service& SessionSocketMgr::GetIOService()
{
    return _io_service;
}

bool SessionSocketMgr::Initialize(std::string const& addr, std::string const& port, uint8 netthread)
{
    if (!_acceptor.Initialize(addr, port))
        return false;
    _NetThreadsCount = netthread;

    return true;
}

void SessionSocketMgr::StartNetwork()
{
    for (uint8 i = 0; i < _NetThreadsCount; ++i)
        _NetThreads.CreateThread(_io_service);
}

void SessionSocketMgr::StopNetwork()
{
    _io_service.stop();
}

void SessionSocketMgr::JoinNetwork()
{
    _NetThreads.JoinAll();
}

void SessionSocketMgr::HandleAccept(SessionSocket* new_sock, const boost::system::error_code& error)
{
    if (!error)
    {
        new_sock->OnOpen();
    }
    else
        delete new_sock;
    _acceptor.RegisterAccept();
}
