/*
** ClientHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 16:52:41 2013 maxime ginters
** Last update Thu Jun 06 03:05:42 2013 maxime ginters
*/

#include "SoundMgr.h"
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
        float speed, speedor;
        uint64 owner;
        bool alive;
        recvData >> guid;
        recvData >> modelid;
        recvData >> name;
        recvData >> x;
        recvData >> y;
        recvData >> z;
        recvData >> o;
        recvData >> owner;
        recvData >> speed;
        recvData >> speedor;
        recvData >> alive;

        if (guid != _player->GetGUID())
        {
            ClientObjectPtr obj(new ClientObject(guid, modelid, name));
            obj->SetClient(this);
            obj->UpdatePosition(x, y, z, o);
            obj->SetSpeed(speed);
            obj->SetSpeedOr(speedor);
            obj->SetAlive(alive);
            AddObject(obj);

            if (modelid == MODELID_BOMB && owner == _player->GetGUID())
                sSoundMgr->PlaySound(SOUND_BOMB_PLANTED);
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

    sSoundMgr->PlaySound(SOUND_NONE);
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
    if (obj->GetModelId() == MODELID_BOMB)
        sSoundMgr->PlaySound(SOUND_BOUM);

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
    std::cout << "REVEIV GRID CHANGE" << std::endl;
    _player->ReadPosition(recvData);
    std::cout << "NEW POS : " << *_player << std::endl;
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

void Client::HandleSendScore(Packet& recvData)
{
    _scoreMgr.ReadScores(recvData);
}

void Client::HandleTeleport(Packet& recvData)
{
    uint64 guid;
    recvData >> guid;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        if (_player->GetGUID() == guid)
            obj = _player;
        else
            return;
    }
    obj->ReadPosition(recvData);
}

void Client::HandlePlayerKilled(Packet& recvData)
{
    uint64 guid;
    uint32 time;
    std::string by;
    uint64 byOwner;
    recvData >> guid;
    recvData >> time;
    recvData >> by;
    recvData >> byOwner;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        if (_player->GetGUID() == guid)
            obj = _player;
        else
            return;
    }

    obj->SetAlive(false);
    obj->SetKilledBy(by);
    obj->SetMovementFlags(0);
    obj->SetRespawnTime(time);
    obj->SetKillerGUID(byOwner);

    std::cout << "OWNER : " << byOwner << "  -  " << _player->GetGUID() << std::endl;
    if (byOwner == _player->GetGUID())
        sSoundMgr->PlaySound(SOUND_ENEMY_DOWN);
}

void Client::HandlePlayerRespawn(Packet& recvData)
{
    uint64 guid;
    recvData >> guid;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        if (_player->GetGUID() == guid)
            obj = _player;
        else
            return;
    }

    obj->SetMovementFlags(0);
    obj->SetAlive(true);
}

void Client::HandleSendGameTimer(Packet& recvData)
{
    recvData >> _gameTimer;
}

void Client::HandleGameFinish(Packet& recvData)
{
    (void)recvData;
    _gameTimer = 0;
    _scoreOpen = true;
}

void Client::HandleMapSaved(Packet& recvData)
{
    (void)recvData;
    _chatBox.PushMessage("Map saved");
}

void Client::HandleUpdateSpeed(Packet& recvData)
{
    uint64 guid;
    float speed;
    recvData >> guid;
    recvData >> speed;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
    {
        if (_player->GetGUID() == guid)
            obj = _player;
        else
            return;
    }

    obj->SetSpeed(speed);
    obj->ReadPosition(recvData);

    if (obj.get() == _player.get())
        sSoundMgr->PlaySound(SOUND_GOGOGO);
}

void Client::HandleBombBoumed(Packet& recvData)
{
    uint64 guid;
    float range;
    recvData >> guid;
    recvData >> range;

    ClientObjectPtr obj = GetObject(guid);
    if (!obj)
        return;
    (void)obj;
    (void)range;

    float x, y;
    obj->GetPosition(x, y);
    x += 2.5f;
    y += 2.5f;
    x = (float)((uint32)x / 5) * 5;
    y = (float)((uint32)y / 5) * 5;
    ClientObjectPtr obj2(new ClientObject(0, 8, "Fire"));
    obj2->UpdatePosition(x, y, 0.0f);
    obj2->SetClient(this);
    obj2->TimedRemove(1500);
    AddClientObject(obj2);
    for (float i = x; i <= x + range; i += 5.0f)
    {
        if (FuzzyCompare(i, x))
            continue;
        if (HasBorderAtPos(i, y))
            break;
        ClientObjectPtr obj2(new ClientObject(0, 8, "Fire"));
        obj2->UpdatePosition(i, y, 0.0f);
        obj2->SetClient(this);
        obj2->TimedRemove(1500);
        AddClientObject(obj2);
        if (HasWallAtPos(i, y))
            break;
    }
    for (float i = x; i >= x - range; i -= 5.0f)
    {
        if (FuzzyCompare(i, x))
            continue;
        if (HasBorderAtPos(i, y))
            break;
        ClientObjectPtr obj2(new ClientObject(0, 8, "Fire"));
        obj2->UpdatePosition(i, y, 0.0f);
        obj2->SetClient(this);
        obj2->TimedRemove(1500);
        AddClientObject(obj2);
        if (HasWallAtPos(i, y))
            break;
    }
    for (float i = y; i <= y + range; i += 5.0f)
    {
        if (FuzzyCompare(i, y))
            continue;
        if (HasBorderAtPos(x, i))
            break;
        ClientObjectPtr obj2(new ClientObject(0, 8, "Fire"));
        obj2->UpdatePosition(x, i, 0.0f);
        obj2->SetClient(this);
        obj2->TimedRemove(1500);
        AddClientObject(obj2);
        if (HasWallAtPos(x, i))
            break;
    }
    for (float i = y; i >= y - range; i -= 5.0f)
    {
        if (FuzzyCompare(i, y))
            continue;
        if (HasBorderAtPos(x, i))
            break;
        ClientObjectPtr obj2(new ClientObject(0, 8, "Fire"));
        obj2->UpdatePosition(x, i, 0.0f);
        obj2->SetClient(this);
        obj2->TimedRemove(1500);
        AddClientObject(obj2);
        if (HasWallAtPos(x, i))
            break;
    }
}
