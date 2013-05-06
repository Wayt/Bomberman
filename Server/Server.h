/*
** Server.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:22:32 2013 maxime ginters
** Last update Mon May 06 18:16:13 2013 maxime ginters
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <boost/asio.hpp>
#include "Shared.h"
#include "RunRunnable.hpp"
#include "SessionSocketAcceptor.h"
#include "SessionSocketMgr.h"

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

private:
    void Update(uint32 const diff);

    SessionSocketMgr _socketMgr;
};

#endif /* !SERVER_H_ */