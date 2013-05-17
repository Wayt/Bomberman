/*
** Client.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:17 2013 maxime ginters
** Last update Fri May 17 17:47:51 2013 maxime ginters
*/

#include "Input.hpp"
#include "Client.h"

Client::Client() :
    _player(NULL), _ioservice(), _status(STATUS_NO_AUTHED),
    _socket(this), _NetThreads(), _recvQueue(), _gameMonitor(NULL), _clientObjectMap(),
    _gameMonitorThread()
{}

Client::~Client()
{
    std::map<uint64, ClientObjectPtr>::iterator itr;
    delete _gameMonitor;
}

bool Client::Start(std::string const& addr, std::string const& port, std::string const& name)
{
    if (!_socket.Connect(addr, port))
        return false;

    _NetThreads.CreateThread(_ioservice);
    run();

    Packet data(CMSG_LOGIN_PLAYER, name.length());
    data << name;
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
    if (_status == STATUS_INGAME)
    {
        std::vector<bool> keys(gdl::Keys::Count, false);
        _gameMonitor->getKeyVector(keys);
        for (uint32 i = 0; i < gdl::Keys::Count; ++i)
            if (keys[i] == true)
                std::cout << "KEY DOWN " << i << std::endl;
        UpdateMovementFlags(keys);

        std::map<uint64, ClientObjectPtr>::iterator itr;
        for (itr = _clientObjectMap.begin(); itr != _clientObjectMap.end(); ++itr)
            itr->second->Update(diff);

        _player->Update(diff);
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

void Client::AddObject(ClientObjectPtr obj)
{
    std::map<uint64, ClientObjectPtr>::const_iterator itr = _clientObjectMap.find(obj->GetGUID());
    if (itr != _clientObjectMap.end())
    {
        sLog->error("Error : try to add an existing object");
        return;
    }
    _clientObjectMap.insert(std::make_pair<uint64, ClientObjectPtr>(obj->GetGUID(), obj));
}

void Client::RemoveObject(ClientObjectPtr obj)
{
    std::map<uint64, ClientObjectPtr>::iterator itr = _clientObjectMap.find(obj->GetGUID());
    if (itr == _clientObjectMap.end())
    {
        sLog->error("Error : try to remove an unknow object");
        return;
    }
    _clientObjectMap.erase(itr);
}

std::map<uint64, ClientObjectPtr>& Client::GetObjectMap()
{
    return _clientObjectMap;
}

void Client::UpdateMovementFlags(std::vector<bool> const& keys)
{
    uint32 size = keys.size();
    for (uint32 i = 0; i < size; ++i)
    {
        if (keys[i])
            UpdatePressed((gdl::Keys::Key)i);
        else
            UpdateNotPressed((gdl::Keys::Key)i);
    }
}

void Client::SendMovementPacket(MovementFlags move, bool add)
{
    Packet data;
    switch (move)
    {
        case MOVEMENT_FORWARD:
            {
                std::cout << "SEND AVANT" << std::endl;
                data.SetOpcode(CMSG_MOVE_FORWARD);
                break;
            }
        case MOVEMENT_BACKWARD:
            {
                std::cout << "SEND ARRIERE" << std::endl;
                data.SetOpcode(CMSG_MOVE_BACKWARD);
                break;
            }
        case MOVEMENT_TURN_LEFT:
            {
                std::cout << "SEND GAUCHE" << std::endl;
                data.SetOpcode(CMSG_MOVE_TURN_LEFT);
                break;
            }
        case MOVEMENT_TURN_RIGHT:
            {
                std::cout << "SEND DROITE" << std::endl;
                data.SetOpcode(CMSG_MOVE_TURN_RIGHT);
                break;
            }
        case MOVEMENT_STRAF_LEFT:
            {
                std::cout << "SEND STRAFT GAUCHE" << std::endl;
                data.SetOpcode(CMSG_MOVE_STRAF_LEFT);
                break;
            }
        case MOVEMENT_STRAF_RIGHT:
            {
                std::cout << "SEND STRAFT DROITE" << std::endl;
                data.SetOpcode(CMSG_MOVE_STRAF_RIGHT);
                break;
            }
        default:
            return;

    }
    data << uint8(add);
    _player->WritePosition(data);
    SendPacket(data);
}

void Client::UpdatePressed(gdl::Keys::Key key)
{
    switch (key)
    {
        case gdl::Keys::W:
            if (_player->AddMovementFlag(MOVEMENT_FORWARD))
                SendMovementPacket(MOVEMENT_FORWARD, true);
            break;
        case gdl::Keys::D:
            if (_player->AddMovementFlag(MOVEMENT_TURN_RIGHT))
                SendMovementPacket(MOVEMENT_TURN_RIGHT, true);
            break;
        case gdl::Keys::S:
            if (_player->AddMovementFlag(MOVEMENT_BACKWARD))
                SendMovementPacket(MOVEMENT_BACKWARD, true);
            break;
        case gdl::Keys::A:
            if (_player->AddMovementFlag(MOVEMENT_TURN_LEFT))
                SendMovementPacket(MOVEMENT_TURN_LEFT, true);
            break;
        case gdl::Keys::Q:
            if (_player->AddMovementFlag(MOVEMENT_STRAF_LEFT))
                SendMovementPacket(MOVEMENT_STRAF_LEFT, true);
            break;
        case gdl::Keys::E:
            if (_player->AddMovementFlag(MOVEMENT_STRAF_RIGHT))
                SendMovementPacket(MOVEMENT_STRAF_RIGHT, true);
            break;
        default:
            break;
    }
}

void Client::UpdateNotPressed(gdl::Keys::Key key)
{
    switch (key)
    {
        case gdl::Keys::W:
            if (_player->RemoveMovementFlag(MOVEMENT_FORWARD))
                SendMovementPacket(MOVEMENT_FORWARD, false);
            break;
        case gdl::Keys::D:
            if (_player->RemoveMovementFlag(MOVEMENT_TURN_RIGHT))
                SendMovementPacket(MOVEMENT_TURN_RIGHT, false);
            break;
        case gdl::Keys::S:
            if (_player->RemoveMovementFlag(MOVEMENT_BACKWARD))
                SendMovementPacket(MOVEMENT_BACKWARD, false);
            break;
        case gdl::Keys::A:
            if (_player->RemoveMovementFlag(MOVEMENT_TURN_LEFT))
                SendMovementPacket(MOVEMENT_TURN_LEFT, false);
            break;
        case gdl::Keys::Q:
            if (_player->RemoveMovementFlag(MOVEMENT_STRAF_LEFT))
                SendMovementPacket(MOVEMENT_STRAF_LEFT, false);
            break;
        case gdl::Keys::E:
            if (_player->RemoveMovementFlag(MOVEMENT_STRAF_RIGHT))
                SendMovementPacket(MOVEMENT_STRAF_RIGHT, false);
            break;
        default:
            break;
    }
}

ClientObjectPtr Client::GetObject(uint64 guid)
{
    std::map<uint64, ClientObjectPtr>::const_iterator itr = _clientObjectMap.find(guid);
    if (itr == _clientObjectMap.end())
        return NULL;
    return itr->second;
}

ClientObjectPtr Client::GetPlayer()
{
    return _player;
}
