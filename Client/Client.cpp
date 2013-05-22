/*
** Client.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:17 2013 maxime ginters
** Last update Wed May 22 17:32:45 2013 fabien casters
*/

#include "Input.hpp"
#include "Client.h"

Client::Client(KeysMap kmap) :
    _player(), _ioservice(), _status(STATUS_NO_AUTHED),
    _socket(this), _NetThreads(), _recvQueue(), _gameMonitor(NULL), _clientObjectMap(),
    _gameMonitorThread(), _keymap(kmap)
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
        UpdateInput(keys);

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

void Client::UpdateInput(std::vector<bool> const& keys)
{
    static KeysBinds binds[6] = {
        {{gdl::Keys::W, gdl::Keys::Z}, MOVEMENT_FORWARD},
        {{gdl::Keys::S, gdl::Keys::S}, MOVEMENT_BACKWARD},
        {{gdl::Keys::A, gdl::Keys::Q}, MOVEMENT_TURN_LEFT},
        {{gdl::Keys::D, gdl::Keys::D}, MOVEMENT_TURN_RIGHT},
        {{gdl::Keys::Q, gdl::Keys::A}, MOVEMENT_STRAF_LEFT},
        {{gdl::Keys::E, gdl::Keys::E}, MOVEMENT_STRAF_RIGHT},
    };

    uint32 size = keys.size();
    for (uint32 i = 0; i < size; ++i)
    {
        if ((gdl::Keys::Key)i == gdl::Keys::Space)
        {
            if (keys[i] && !_spaceAction)
            {
                HandleSpaceAction();
                _spaceAction = true;
            }
            else if (!keys[i])
                _spaceAction = false;

        }
        else
            for (uint8 j = 0; j < 6; ++j)
            {
                if (binds[j].key[_keymap] == (gdl::Keys::Key)i)
                {
                    if (keys[i])
                    {
                        if (_player->AddMovementFlag(binds[j].movement))
                            SendMovementPacket(binds[j].movement, true);
                    }
                    else
                    {
                        if (_player->RemoveMovementFlag(binds[j].movement))
                            SendMovementPacket(binds[j].movement, false);
                    }
                    break;
                }

            }
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

void Client::HandleSpaceAction()
{
    Packet data(CMSG_DROP_BOMB, 0);
    SendPacket(data);
}
