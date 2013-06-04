/*
** ClientHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 16:52:41 2013 maxime ginters
** Last update Tue Jun 04 15:00:45 2013 maxime ginters
*/

#include "Client.h"

void Client::HandleLoginResponse(Packet& recvData)
{
    uint8 result;
    recvData >> result;

    if (result != LOGIN_RESPONSE_OK)
    {
        sLog->error("Fail to auth with server");
        Stop();
        return;
    }

    uint64 guid;
    std::string name;
    uint32 modelid;
    recvData >> guid;
    recvData >> name;
    recvData >> modelid;
    _player = new ClientObject(guid, modelid, name);
    _player->SetClient(this);
    _status = STATUS_AUTHED;
    sLog->out("Successful authed to server");

    Packet data(CMSG_ENTER_GAME);
    SendPacket(data);
}

void Client::HandleSendObject(Packet& recvData)
{
    uint32 count;
    recvData >> count;

    std::cout << "RECEIV " << count << " OBJECT(S)" << std::endl;
    for (uint32 i = 0; i < count; ++i)
    {
        uint64 guid;
        uint32 modelid;
        std::string name;
        float x, y, z, o;
        recvData >> guid;
        recvData >> modelid;
        recvData >> name;
        recvData >> x;
        recvData >> y;
        recvData >> z;
        recvData >> o;

        if (guid != _player->GetGUID())
        {
            ClientObjectPtr obj(new ClientObject(guid, modelid, name));
            obj->SetClient(this);
            obj->UpdatePosition(x, y, z, o);
            //if (modelid == 0 || modelid == 2)
                AddObject(obj);
            //std::cout << "OBJECT : " << name << " guid : " << guid << std::endl;
        }
    }
}

void Client::HandleAddToMap(Packet& recvData)
{
    if (_gameMonitor)
    {
        sLog->error("Error : receiv add to map but already in map");
        return;
    }
    uint32 width, height;

    recvData >> width;
    recvData >> height;
    _player->ReadPosition(recvData);

    std::cout << "Map size : " << width << " / " << height << " pos : " << *(_player->GetPosition()) << std::endl;
    // Process add to map
    _status = STATUS_INGAME;

    _gameMonitor = new GameMonitor(this, width, height);
    _gameMonitorThread.CreateThread(*_gameMonitor);
}

void Client::HandleUpdateMoveflags(Packet& recvData)
{
    uint64 guid;
    uint32 flags;
    recvData >> guid;
    recvData >> flags;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        sLog->error("Error: receiv SMSG_UPDATE_MOVEFLAGS for an unknow guid");
        return;
    }

    obj->SetMovementFlags(flags);
    obj->ReadPosition(recvData);

    std::cout << "Object : " << obj->GetGUID() << " POS : " << *obj->GetPosition() << std::endl;
}

void Client::HandleDeleteObject(Packet& recvData)
{
    uint64 guid;
    recvData >> guid;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        sLog->error("Error: receiv SMSG_UPDATE_MOVEFLAGS for an unknow guid");
        return;
    }

    RemoveObject(obj);
}

void Client::HandleForcePosition(Packet& recvData)
{
    sLog->out("Forcing player position ...");
    _player->ReadPosition(recvData);
}

void Client::HandleGlobalChatText(Packet& recvData)
{
    std::string msg;
    recvData >> msg;
    _chatBox.PushMessage(msg);
}

#define ABS(v) ((v) > 0 ? (v) : -(v))
#define GRIDPOS(v) (int32(v) - (int32(v) % GRID_SIZE))
#define DISTX(a, b) (ABS(((GRIDPOS(a->GetPositionX())) - (GRIDPOS(b->GetPositionX())))))
#define DISTY(a, b) (ABS(((GRIDPOS(a->GetPositionY())) - (GRIDPOS(b->GetPositionY())))))

void Client::HandleGridChange(Packet& recvData)
{
    _player->ReadPosition(recvData);
    std::map<uint64, ClientObjectPtr>::iterator itr;
    for (itr = _clientObjectMap.begin(); itr != _clientObjectMap.end();)
    {
        if (DISTX(_player, itr->second) > GRID_SIZE ||
                DISTY(_player, itr->second) > GRID_SIZE)
            _clientObjectMap.erase(itr++);
        else
            ++itr;
    }

}

void Client::HandleKilled(Packet& recvData)
{
    uint32 time;
    std::string by;
    recvData >> time;
    recvData >> by;

    std::cout << "Killed by : " << by << " respawn in " << time << "ms" << std::endl;
    _player->SetAlive(false);
    _player->SetKilledBy(by);
    _player->SetMovementFlags(0);
    _player->SetRespawnTime(time);
}

void Client::HandleSendScore(Packet& recvData)
{
    _scoreMgr.ReadScores(recvData);
}

void Client::HandleTeleport(Packet& recvData)
{
    _player->ReadPosition(recvData);
}
