/*
** Client.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:17 2013 maxime ginters
** Last update Wed Jun 05 20:26:36 2013 maxime ginters
*/

#include "Input.hpp"
#include "Client.h"

Client::Client(KeysMap kmap) :
    _player(), _ioservice(), _status(STATUS_NO_AUTHED),
    _socket(this), _NetThreads(), _recvQueue(), _gameMonitor(NULL), _clientObjectMap(),
    _gameMonitorThread(), _keymap(kmap), _chatBox(), _pingData(), _scoreOpen(false),
    _scoreMgr(), _gameTimer(0)
{
    _pingData[PING_INTERVAL] = 5000;
}

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

        if (IsFinish())
            return;

        std::map<uint64, ClientObjectPtr>::iterator itr;
        for (itr = _clientObjectMap.begin(); itr != _clientObjectMap.end(); ++itr)
            itr->second->Update(diff);

        _player->Update(diff);
        _player->UpdateRespawnTime(diff);

        if (_pingData[PING_INTERVAL] <= diff)
        {
            Packet data(CMSG_PING, 0);
            _pingData[PING_TIME] = GetMSTime();
            SendPacket(data);
            _pingData[PING_INTERVAL] = 5000;
        }
        else
            _pingData[PING_INTERVAL] -= diff;

        if (_gameTimer <= diff)
            _gameTimer = 0;
        else
            _gameTimer -= diff;
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

void Client::GetObjectMap(std::map<uint64, ClientObjectPtr>& map) const
{
    uint32 size = 0;
    std::map<uint64, ClientObjectPtr>::const_iterator itr = _clientObjectMap.begin();
    for (; itr != _clientObjectMap.end(); ++itr)
    {
        ++size;
        map[itr->first] = itr->second;
    }
}

void Client::UpdateInput(std::vector<bool> const& keys)
{
    static std::vector<bool> prevKeys(gdl::Keys::Count, false);

    uint32 size = keys.size();
    for (uint32 i = 0; i < size; ++i)
    {
        if (keys[i] && !prevKeys[i])
            HandleKeyDown((gdl::Keys::Key)i);
        else if (!keys[i] && prevKeys[i])
            HandleKeyUp((gdl::Keys::Key)i);
        prevKeys[i] = keys[i];
    }
}

KeysBinds const* Client::GetKeyBinds() const
{
    static KeysBinds binds[6] = {
        {{gdl::Keys::W, gdl::Keys::Z}, MOVEMENT_FORWARD},
        {{gdl::Keys::S, gdl::Keys::S}, MOVEMENT_BACKWARD},
        {{gdl::Keys::A, gdl::Keys::Q}, MOVEMENT_TURN_LEFT},
        {{gdl::Keys::D, gdl::Keys::D}, MOVEMENT_TURN_RIGHT},
        {{gdl::Keys::Q, gdl::Keys::A}, MOVEMENT_STRAF_LEFT},
        {{gdl::Keys::E, gdl::Keys::E}, MOVEMENT_STRAF_RIGHT},
    };
    return binds;
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
    if (!IsFinish() && !_player->IsAlive())
        return;

    Packet data(CMSG_DROP_BOMB, 0);
    SendPacket(data);
}

void Client::HandleSendChat()
{
    std::string str = _chatBox.GetInputString();
    if (str.length() == 0)
        return;
    Packet data(CMSG_SEND_GLOBALTEXT, str.length());
    data << str;
    SendPacket(data);
}

void Client::HandleKeyDown(gdl::Keys::Key key)
{
    std::cout << "KEYDOWN : " << (uint32)key << std::endl;
    if (_chatBox.IsOpen() && key != gdl::Keys::Return)
    {
        _chatBox.HandleInput((int)key);
        return;
    }

    switch (key)
    {
        case gdl::Keys::Space:
                HandleSpaceAction();
                return;
        case gdl::Keys::Return:
                if (_chatBox.IsOpen())
                {
                    _chatBox.EndInput();
                    HandleSendChat();
                }
                else
                    _chatBox.StartInput();
                return;
        case gdl::Keys::Tab:
                if (!IsFinish())
                    _scoreOpen = true;
                break;
        case gdl::Keys::M:
                if (!IsFinish())
                    SaveMapRequest();
                break;
        default:
                break;

    }

    if (!_player->IsAlive())
        return;

    KeysBinds const* binds = GetKeyBinds();
    for (uint8 j = 0; j < 6; ++j)
    {
        if (binds[j].key[_keymap] == key)
        {
            if (_player->AddMovementFlag(binds[j].movement))
                SendMovementPacket(binds[j].movement, true);

            if (binds[j].movement == MOVEMENT_STRAF_LEFT)
                _player->UpdateOrientation(_player->GetOrientation() + M_PI_4);
            else if (binds[j].movement == MOVEMENT_STRAF_RIGHT)
                _player->UpdateOrientation(_player->GetOrientation() - M_PI_4);
        }
    }
}

void Client::HandleKeyUp(gdl::Keys::Key key)
{
    std::cout << "KEYUP : " << (uint32)key << std::endl;

    if (IsFinish())
        return;

    if (key == gdl::Keys::Tab)
        _scoreOpen = false;

    if (_chatBox.IsOpen() || !_player->IsAlive())
        return;

    KeysBinds const* binds = GetKeyBinds();
    for (uint8 j = 0; j < 6; ++j)
    {
        if (binds[j].key[_keymap] == key)
        {
            if (_player->RemoveMovementFlag(binds[j].movement))
                SendMovementPacket(binds[j].movement, false);

            if (binds[j].movement == MOVEMENT_STRAF_LEFT)
                _player->UpdateOrientation(_player->GetOrientation() - M_PI_4);
            else if (binds[j].movement == MOVEMENT_STRAF_RIGHT)
                _player->UpdateOrientation(_player->GetOrientation() + M_PI_4);
        }
    }
}

ChatBox const& Client::GetChatBox() const
{
    return _chatBox;
}

void Client::HandleReceivPong()
{
    _pingData[PING_LATENCY] = GetMSTimeDiffToNow(_pingData[PING_TIME]);
    sLog->out("Latency : %u", _pingData[PING_LATENCY]);
}

void Client::GetObjectList(std::list<GameObject*> &list) const
{
    std::map<uint64, ClientObjectPtr>::const_iterator it;
    for (it = _clientObjectMap.begin(); it != _clientObjectMap.end(); ++it)
    {
        ClientObjectPtr ma_super_variable_useless_mais_que_je_sais_pas_faire_autrement_et_que_jai_la_fleme_de_chercher = it->second;
        list.push_back(ma_super_variable_useless_mais_que_je_sais_pas_faire_autrement_et_que_jai_la_fleme_de_chercher.get());
    }
}

bool Client::IsScoreOpen() const
{
    return _scoreOpen;
}

ScoreMgr const& Client::GetScoreMgr() const
{
    return _scoreMgr;
}

uint32 Client::GetGameTimer() const
{
    return _gameTimer;
}

bool Client::IsFinish() const
{
    return _gameTimer == 0;
}

void Client::SaveMapRequest()
{
    Packet data(CMSG_SAVE_MAP, 0);
    SendPacket(data);
}
