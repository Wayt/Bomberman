/*
** SessionHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:42:46 2013 maxime ginters
** Last update Fri May 17 19:08:21 2013 maxime ginters
*/

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
    _player->UpdatePosition(5.0f, 5.0f, 0.0f, 0.0f);
    _player->WritePosition(data);

    SendPacket(data);

    map->AddObject(_player);
     _status = STATUS_INGAME;
}

void Session::HandleMovement(Packet& recvData)
{
    bool add;
    recvData >> add;
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
            std::cout << "EN STRAF GAUCHE" << std::endl;
            break;
        case CMSG_MOVE_STRAF_RIGHT:
            _player->UpdateMovementFlag(MOVEMENT_STRAF_RIGHT, add);
            std::cout << "EN STRAF DROITE" << std::endl;
            break;
        default:
            break;
    }
    _player->ReadPosition(recvData);

    _player->GetMap()->GridUpdater(_player, GRIDUPDATE_MOVEFLAGS, UPDATE_FULL);

    std::cout << "POS : " << *_player->GetPosition() << " GRID : " << _player->GetGrid() << std::endl;
}
