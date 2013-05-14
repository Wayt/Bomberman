/*
** ClientHandler.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 16:52:41 2013 maxime ginters
** Last update Tue May 14 17:55:17 2013 maxime ginters
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

    recvData >> _guid;
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
        std::cout << "OBJECT : " << name << " guid : " << guid << std::endl;
        // read object;
    }
}

void Client::HandleAddToMap(Packet& recvData)
{
    uint32 width, height;

    recvData >> width;
    recvData >> height;
    recvData >> _modelId;
    _pos.ReadPosition(recvData);

    std::cout << "Map size : " << width << " / " << height << " pos : " << _pos << std::endl;
    // Process add to map

    _status = STATUS_INGAME;
}