/*
** Client.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:11 2013 maxime ginters
** Last update Wed May 15 17:25:43 2013 maxime ginters
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <string>
#include <boost/asio.hpp>
#include "Shared.h"
#include "ClientSocket.h"
#include "Position.h"
#include "GameMonitor.h"
#include "ClientObject.h"

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
    void HandleSendObject(Packet& recvData);
    void HandleAddToMap(Packet& recvData);

    void AddObject(ClientObject* obj);

    std::map<uint64, ClientObject*> const& GetObjectMap() const;

private:
    void Update(uint32 const diff);

    std::string _name;
    uint64 _guid;
    Position _pos;
    uint32 _modelId;
    boost::asio::io_service _ioservice;
    OpcodeStatus _status;
    ClientSocket _socket;
    RunnablePool<boost::asio::io_service> _NetThreads;
    LockedQueue<Packet> _recvQueue;
    GameMonitor* _gameMonitor;
    std::map<uint64, ClientObject*> _clientObjectMap;
    RunnablePool<GameMonitor> _gameMonitorThread;
};

#endif /* !CLIENT_H_ */
