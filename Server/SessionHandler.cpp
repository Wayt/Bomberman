/*
** SessionHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:42:46 2013 maxime ginters
** Last update Tue Jun 04 14:41:30 2013 maxime ginters
*/

#include "Bomb.h"
#include "Session.h"
#include "Map.h"
#include "Server.h"

void Session::HandleLoginPlayer(Packet& recvData)
{
    std::string name;
    recvData >> name;

    std::cout << "Player name : " << name << std::endl;
    // Check nick availability

    _status = STATUS_AUTHED;
    Map* map = _server->GetMap();
    _player = new Player(map->MakeNewGuid(), name, this);

    Packet data(SMSG_LOGIN_RESPONSE, 9 + name.length() + 4);
    data << uint8(LOGIN_RESPONSE_OK);
    data << uint64(_player->GetGUID());
    data << _player->GetName();
    data << uint32(_player->GetModelId());
    SendPacket(data);
}

void Session::HandleEnterGame(Packet& recvData)
{
    (void)recvData;

    uint32 width, height;

    Map* map = _server->GetMap();
    map->GetWidthAndHeight(width, height);

    Packet data(SMSG_ADD_TO_MAP, 20);
    data << uint32(width * MAP_PRECISION);
    data << uint32(height * MAP_PRECISION);
    float x, y;
    map->GetRandomStartPosition(x, y);
    _player->UpdatePosition(x, y, 0.0f, 0.0f);
    _player->WritePosition(data);

    SendPacket(data);

    map->AddObject(_player);
    map->GetScoreMgr().AddPlayer(_player);
    _status = STATUS_INGAME;
    map->SendScores();
}

void Session::HandleMovement(Packet& recvData)
{
    bool add;
    recvData >> add;

    if (!_player->IsAlive())
        return;

    _player->ReadPosition(recvData);

    switch (recvData.GetOpcode())
    {
        case CMSG_MOVE_FORWARD:
            _player->UpdateMovementFlag(MOVEMENT_FORWARD, add);
            std::cout << "EN AVANT " << add << std::endl;
            break;
        case CMSG_MOVE_BACKWARD:
            _player->UpdateMovementFlag(MOVEMENT_BACKWARD, add);
            std::cout << "EN ARRIERE " << add << std::endl;
            break;
        case CMSG_MOVE_TURN_LEFT:
            _player->UpdateMovementFlag(MOVEMENT_TURN_LEFT, add);
            std::cout << "EN GAUCHE " << add << std::endl;
            break;
        case CMSG_MOVE_TURN_RIGHT:
            _player->UpdateMovementFlag(MOVEMENT_TURN_RIGHT, add);
            std::cout << "EN DROITE " << add << std::endl;
            break;
        case CMSG_MOVE_STRAF_LEFT:
            _player->UpdateMovementFlag(MOVEMENT_STRAF_LEFT, add);
            _player->UpdateOrientation(_player->GetOrientation() + (add ? M_PI_4 : -M_PI_4));
            std::cout << "EN STRAF GAUCHE" << std::endl;
            break;
        case CMSG_MOVE_STRAF_RIGHT:
            _player->UpdateMovementFlag(MOVEMENT_STRAF_RIGHT, add);
            _player->UpdateOrientation(_player->GetOrientation() + (add ? -M_PI_4 : M_PI_4));
            std::cout << "EN STRAF DROITE" << std::endl;
            break;
        default:
            break;
    }
    Position pos;
    _player->GetPosition(pos);

    std::cout << "OLD POS : " << pos << std::endl;
    std::cout << "NEW POS : " << *_player->GetPosition() << std::endl;
    std::cout << "Decalage : " << _player->GetDistance2d(&pos) << std::endl;

    if (_player->GetDistance2d(&pos) >= 0.5f)
    {
        float x, y, z, o;
        pos.GetPosition(x, y, z, o);
        _player->UpdatePosition(x, y, z, o);
        Packet data(SMSG_FORCE_POSITION, 4 + 4 + 4 + 4);
        _player->WritePosition(data);
        SendPacket(data);
    }

    _player->GetMap()->GridUpdater(_player, GRIDUPDATE_MOVEFLAGS, UPDATE_FULL);
}

void Session::HandleDropBomb(Packet& recvData)
{
    (void)recvData;
    float x, y, z, o;
    _player->GetPosition(x, y, z, o);

    Bomb* bomb = new Bomb(_player->GetMap()->MakeNewGuid(), _player);
    bomb->UpdatePosition(x, y, z, 0.0f);
    _player->GetMap()->AddObject(bomb);
    std::cout << "BOMB PLANTED" << std::endl;

    if (Score* sc = _player->GetMap()->GetScoreMgr().GetScore(_player->GetGUID()))
    {
        sc->bomb += 1;
        _player->GetMap()->SendScores(_player->GetGUID());
    }
}

void Session::HandleGlobalChatText(Packet& recvData)
{
    std::string msg;
    recvData >> msg;

    std::stringstream ss;
    ss << _player->GetName();
    ss << " : ";
    ss << msg;

    Packet data(SMSG_SEND_GLOBALTEXT, ss.str().length());
    data << ss.str();
   _server->BroadcastToAll(data);
}

