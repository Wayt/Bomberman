/*
** Session.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 15:47:46 2013 maxime ginters
** Last update Mon May 27 13:57:04 2013 maxime ginters
*/

#ifndef SESSION_H_
# define SESSION_H_

#include "Shared.h"
#include "SessionSocket.h"
#include "Opcodes.h"
#include "Packet.hpp"
#include "Player.h"

class Server;

class Session
{
public:
    Session(SessionSocket* sock, Server* srv);

    SessionSocket* GetSessionSocket();
    OpcodeStatus GetStatus() const;

    void QueuePacket(Packet* pkt);
    void SendPacket(Packet const& pkt);

    bool Update(uint32 const diff);

    void Close();
    bool IsClosing() const;
    void HandleLogout();

    // Handler
    void HandleLoginPlayer(Packet& recvData);
    void HandleEnterGame(Packet& recvData);
    void HandleMovement(Packet& recvData);
    void HandleDropBomb(Packet& recvData);
    void HandleGlobalChatText(Packet& recvData);

private:
    SessionSocket* _socket;
    OpcodeStatus _status;
    LockedQueue<Packet> _recvQueue;
    Server* _server;
    bool _closing;
    Player* _player;
};

#endif /* !SESSION_H_ */
