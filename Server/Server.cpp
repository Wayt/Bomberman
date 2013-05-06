/*
** Server.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 13:44:25 2013 maxime ginters
** Last update Mon May 06 15:59:25 2013 maxime ginters
*/

#include <iostream>
#include <unistd.h>
#include "Server.h"

Server::Server() : _io_service(), _NetThreads(), _acceptor(_io_service),
    _NetThreadsCount(1)
{}

Server::~Server()
{}

bool Server::Initialize(std::string const& addr, std::string const& port, uint8 netthread)
{
    if (!_acceptor.Initialize(addr, port))
        return false;
    _NetThreadsCount = netthread;

    // prepare map
    return true;
}

void Server::Start()
{
    for (uint8 i = 0; i < _NetThreadsCount; ++i)
        _NetThreads.CreateThread(_io_service);
    run();
}

void Server::Stop()
{
    stop();
    _io_service.stop();
}

void Server::Join()
{
    join();
    _NetThreads.JoinAll();
}

void Server::operator()()
{
    uint32 prevTime = GetMSTime();
    uint32 currTime = 0;
    uint32 prevSleep = 0;
    while (!isStopped())
    {
        currTime = GetMSTime();
        uint32 diff = GetMSTimeDiff(prevTime, currTime);

        Update(diff);
        prevTime = currTime;

        if (diff <= SERVER_SLEEP_TIME + prevSleep)
        {
            prevSleep = SERVER_SLEEP_TIME + prevSleep - diff;
            usleep(prevSleep * IN_MILLISECONDS);
        }
        else
            prevSleep = 0;
    }

}

void Server::Update(uint32 const diff)
{
    (void)diff;
    sleep(10);
}
