/*
** Client.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:17 2013 maxime ginters
** Last update Wed May 15 16:19:40 2013 fabien casters
*/

#include "Client.h"

Client::Client(std::string const& name) :
    _name(name), _guid(0), _pos(), _modelId(0), _ioservice(), _status(STATUS_NO_AUTHED),
    _socket(this), _NetThreads(), _recvQueue(), _gameMonitor(NULL), _clientObjectMap()
{}

Client::~Client()
{
    std::map<uint64, ClientObject*>::iterator itr;
    for (itr = _clientObjectMap.begin(); itr != _clientObjectMap.end(); ++itr)
        delete itr->second;
}

bool Client::Start(std::string const& addr, std::string const& port)
{
    if (!_socket.Connect(addr, port))
        return false;

    _NetThreads.CreateThread(_ioservice);
    run();

    Packet data(CMSG_LOGIN_PLAYER, _name.length());
    data << _name;
    SendPacket(data);
    return true;
}

void Client::Stop()
{
    _ioservice.stop();
    _socket.Close();
    stop();
}

void Client::Join()
{
    _NetThreads.JoinAll();
    join();
}

void Client::operator()()
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

        if (diff <= CLIENT_SLEEP_TIME + prevSleep)
        {
            prevSleep = CLIENT_SLEEP_TIME + prevSleep - diff;
            usleep(prevSleep * IN_MILLISECONDS);
        }
        else
            prevSleep = 0;
    }
}

boost::asio::io_service& Client::GetIOService()
{
    return _ioservice;
}

void Client::Update(uint32 const diff)
{
    (void)diff;
    uint32 size = _recvQueue.size();
    for (uint32 i = 0; i < size && !_recvQueue.empty() && _socket.IsOpen(); ++i)
    {
        Packet* pkt = _recvQueue.get();
        if (!pkt)
            continue;

        OpcodeHandler const* opcodehandler = sOpcodesMgr->GetOpcodeHandler((Opcodes)pkt->GetOpcode());
        if (!opcodehandler)
        {
            sLog->error("Error: receiv an unknow opcode : 0x%x", pkt->GetOpcode());
            delete pkt;
            continue;
        }

        if (_status != opcodehandler->status)
        {
            sLog->error("Error: invalide packet status for opcode : 0x%x, current : %u - requested : %u", pkt->GetOpcode(), _status, opcodehandler->status);
            delete pkt;
            continue;
        }

        if (opcodehandler->cli_handler)
            (this->*(opcodehandler->cli_handler))(*pkt);

        delete pkt;
    }
}

void Client::QueuePacket(Packet* packet)
{
    _recvQueue.add(packet);
}

void Client::SendPacket(Packet const& packet)
{
    _socket.SendPacket(&packet);
}

void Client::AddObject(ClientObject* obj)
{
    std::map<uint64, ClientObject*>::const_iterator itr = _clientObjectMap.find(obj->GetGUID());
    if (itr != _clientObjectMap.end())
    {
        sLog->error("Error : try to add an existing object");
        return;
    }
    _clientObjectMap.insert(std::make_pair<uint64, ClientObject*>(obj->GetGUID(), obj));
}
