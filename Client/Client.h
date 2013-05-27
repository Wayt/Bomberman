/*
** Client.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 13:57:11 2013 maxime ginters
** Last update Mon May 27 19:24:05 2013 vincent leroy
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
#include "ChatBox.h"

#define CLIENT_SLEEP_TIME 20

using boost::asio::ip::tcp;

enum KeysMap
{
    KEYMAP_US   = 0,
    KEYMAP_FR   = 1
};

struct KeysBinds
{
    gdl::Keys::Key key[2]; // 0 US - 1 FR
    MovementFlags movement;
};

class Client : public Runnable
{
public:
    explicit Client(KeysMap kmap = KEYMAP_US);
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
    void HandleForcePosition(Packet& recvData);
    void HandleGlobalChatText(Packet& recvData);

    void AddObject(ClientObjectPtr obj);
    void RemoveObject(ClientObjectPtr obj);

    std::map<uint64, ClientObjectPtr>& GetObjectMap();
    ClientObjectPtr GetObject(uint64 guid);
    ClientObjectPtr GetPlayer();
    ChatBox const& GetChatBox() const;

    void HandleReceivPong();

    void GetObjectList(std::list<const GameObject*> &list) const;

private:
    void Update(uint32 const diff);
    void UpdateInput(std::vector<bool> const& keys);
    void HandleKeyDown(gdl::Keys::Key key);
    void HandleKeyUp(gdl::Keys::Key key);
    void SendMovementPacket(MovementFlags move, bool add);
    KeysBinds const* GetKeyBinds() const;

    void HandleSpaceAction();
    void HandleSendChat();

    ClientObjectPtr _player;

    boost::asio::io_service _ioservice;
    OpcodeStatus _status;
    ClientSocket _socket;
    RunnablePool<boost::asio::io_service> _NetThreads;
    LockedQueue<Packet> _recvQueue;
    GameMonitor* _gameMonitor;
    std::map<uint64, ClientObjectPtr> _clientObjectMap;
    RunnablePool<GameMonitor> _gameMonitorThread;
    KeysMap _keymap;
    ChatBox _chatBox;

    enum PingData
    {
        PING_INTERVAL   = 0,
        PING_TIME       = 1,
        PING_LATENCY    = 2,
        PING_SIZE       = 3
    };
    uint32 _pingData[PING_SIZE];
};

#endif /* !CLIENT_H_ */
