/*
** Server.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:22:32 2013 maxime ginters
** Last update Mon May 13 18:36:46 2013 maxime ginters
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <boost/asio.hpp>
#include "Shared.h"
#include "RunRunnable.hpp"
#include "SessionSocketAcceptor.h"
#include "SessionSocketMgr.h"
#include "Map.h"

#define SERVER_SLEEP_TIME 50

class Server : public Runnable
{
public:
    Server();
    ~Server();

    bool Initialize(std::string const& addr, std::string const& port = "9000", uint8 netthread = 2);

    void Start();
    void Stop();
    void Join();

    void operator()();

    void AddSession(Session* sess);

private:
    void Update(uint32 const diff);
    void UpdateSessions(uint32 const diff);

    SessionSocketMgr _socketMgr;
    LockedQueue<Session> _addSessionQueue;
    std::list<Session*> _sessionList;
    Map* _map;
};

#endif /* !SERVER_H_ */
