/*
** Session.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 15:47:46 2013 maxime ginters
** Last update Fri May 10 16:08:15 2013 maxime ginters
*/

#ifndef SESSION_H_
# define SESSION_H_

#include "Shared.h"
#include "SessionSocket.h"
#include "Opcodes.h"
#include "Packet.hpp"

class Server;

class Session
{
public:
    Session(SessionSocket* sock, Server* srv);

    SessionSocket* GetSessionSocket();
    OpcodeStatus GetStatus() const;

    void QueuePacket(Packet* pkt);

    bool Update(uint32 const diff);

    void Close();
    void HandleLogout();

    // Handler
    void HandlePlayerName(Packet& recvData);

private:
    SessionSocket* _socket;
    OpcodeStatus _status;
    LockedQueue<Packet> _recvQueue;
    Server* _server;
    bool _closing;
};

#endif /* !SESSION_H_ */
