/*
** Server.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 13:44:25 2013 maxime ginters
** Last update Tue Jun 04 16:22:09 2013 maxime ginters
*/

#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "Session.h"

Server::Server() : _socketMgr(this), _addSessionQueue(),
    _sessionList(), _map(NULL)
{}

Server::~Server()
{}

bool Server::Initialize(std::string const& addr, std::string const& port, uint8 netthread)
{
    if (!_socketMgr.Initialize(addr, port, netthread))
        return false;

    // prepare map
    _map = Map::CreateNewRandomMap(10, 10, 0.9f, 0.9f);
    return true;
}

void Server::Start()
{
    run();
    _socketMgr.StartNetwork();
}

void Server::Stop()
{
    _socketMgr.StopNetwork();
    stop();
}

void Server::Join()
{
    _socketMgr.JoinNetwork();
    join();
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

void Server::AddSession(Session* sess)
{
    _addSessionQueue.add(sess);
}

void Server::Update(uint32 const diff)
{
    UpdateSessions(diff);

    if (_map)
        _map->Update(diff);
}

void Server::UpdateSessions(uint32 const diff)
{
    Session* sess = NULL;
    while ((sess = _addSessionQueue.get()) != NULL)
        _sessionList.push_back(sess);

    std::list<Session*>::iterator itr = _sessionList.begin();
    std::list<Session*>::iterator next;
    for (; itr != _sessionList.end(); itr = next)
    {
        next = itr;
        ++next;

        if ((sess = (*itr)) != NULL)
        {
            if (!sess->Update(diff))
            {
                sess->HandleLogout();
                _sessionList.erase(itr);
                delete sess;

            }
        }
    }
}

Map const* Server::GetMap() const
{
    return _map;
}

Map* Server::GetMap()
{
    return _map;
}

void Server::BroadcastToAll(Packet& pkt)
{
    std::list<Session*>::iterator itr = _sessionList.begin();
    for (; itr != _sessionList.end(); ++itr)
    {
        if (Session* sess = (*itr))
            if (sess->GetStatus() == STATUS_INGAME)
                sess->SendPacket(pkt);
    }
}

