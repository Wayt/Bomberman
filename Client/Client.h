/*
** Client.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:11 2013 maxime ginters
** Last update Fri May 17 17:10:57 2013 maxime ginters
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
#include "Input.hpp"

#define CLIENT_SLEEP_TIME 20

using boost::asio::ip::tcp;

class Client : public Runnable
{
public:
    explicit Client();
    virtual ~Client();

    bool Start(std::string const& addr, std::string const& port, std::string const& name);
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
    void HandleUpdateMoveflags(Packet& recvData);
    void HandleDeleteObject(Packet& recvData);

    void AddObject(ClientObjectPtr obj);
    void RemoveObject(ClientObjectPtr obj);

    std::map<uint64, ClientObjectPtr>& GetObjectMap();
    ClientObjectPtr GetObject(uint64 guid);
    ClientObjectPtr GetPlayer();

private:
    void Update(uint32 const diff);
    void UpdateMovementFlags(std::vector<bool> const& keys);
    void SendMovementPacket(MovementFlags move, bool add);
    void UpdatePressed(gdl::Keys::Key key);
    void UpdateNotPressed(gdl::Keys::Key key);


    ClientObjectPtr _player;

    boost::asio::io_service _ioservice;
    OpcodeStatus _status;
    ClientSocket _socket;
    RunnablePool<boost::asio::io_service> _NetThreads;
    LockedQueue<Packet> _recvQueue;
    GameMonitor* _gameMonitor;
    std::map<uint64, ClientObjectPtr> _clientObjectMap;
    RunnablePool<GameMonitor> _gameMonitorThread;
};

#endif /* !CLIENT_H_ */
