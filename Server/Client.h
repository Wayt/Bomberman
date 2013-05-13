/*
** Client.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:11 2013 maxime ginters
** Last update Mon May 13 16:52:30 2013 maxime ginters
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <string>
#include <boost/asio.hpp>
#include "Shared.h"
#include "ClientSocket.h"

#define CLIENT_SLEEP_TIME 20

using boost::asio::ip::tcp;

class Client : public Runnable
{
public:
    explicit Client(std::string const& name);
    virtual ~Client();

    bool Start(std::string const& addr, std::string const& port);
    void operator()();
    void Stop();
    void Join();

    boost::asio::io_service& GetIOService();

    void QueuePacket(Packet* packet);
    void SendPacket(Packet const& packet);


    // Handlers
    void HandleLoginResponse(Packet& recvData);

private:
    void Update(uint32 const diff);

    std::string _name;
    boost::asio::io_service _ioservice;
    OpcodeStatus _status;
    ClientSocket _socket;
    RunnablePool<boost::asio::io_service> _NetThreads;
    LockedQueue<Packet> _recvQueue;
};

#endif /* !CLIENT_H_ */
