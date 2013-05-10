/*
** Session.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 15:52:15 2013 maxime ginters
** Last update Fri May 10 16:16:38 2013 maxime ginters
*/

#include <iostream>
#include "Session.h"
#include "Server.h"

Session::Session(SessionSocket* sock, Server* srv) :
    _socket(sock), _status(STATUS_NO_AUTHED),
    _recvQueue(), _server(srv), _closing(false)
{
    _server->AddSession(this);
}

SessionSocket* Session::GetSessionSocket()
{
    return _socket;
}

OpcodeStatus Session::GetStatus() const
{
    return _status;
}

void Session::QueuePacket(Packet* pkt)
{
    _recvQueue.add(pkt);
}

void Session::Close()
{
    _closing = true;
}

void Session::HandleLogout()
{
    std::cout << "Logout session" << std::endl;
    _socket->Close();
    delete _socket;
    _socket = NULL;
}

bool Session::Update(uint32 const diff)
{
    std::cout << "Session::Update" << std::endl;
    if (_closing)
        return false;

    (void)diff;
    uint32 size = _recvQueue.size();
    for (uint32 i = 0; i < size && !_recvQueue.empty() && _socket && !_socket->IsClosed(); ++i)
    {
        Packet* pkt = _recvQueue.get();
        if (!pkt)
            continue;

        OpcodeHandler const* opcodehandler = sOpcodesMgr->GetOpcodeHandler(pkt->GetOpcode());
        if (!opcodehandler)
        {
            sLog->error("Error: receiv an unknow opcode : 0x%x", pkt->GetOpcode());
            delete pkt;
            continue;
        }

        if (_status != opcodehandler->status)
        {
            sLog->error("Error: invalide packet status, current : %u - requested : %u", _status, opcodehandler->status);
            delete pkt;
            continue;
        }

        if (opcodehandler->handler)
            (this->*(opcodehandler->handler))(*pkt);

        delete pkt;
    }
    return true;
}

