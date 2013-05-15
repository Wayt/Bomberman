/*
** ClientSocket.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 14:26:00 2013 maxime ginters
** Last update Mon May 13 17:04:23 2013 maxime ginters
*/

#ifndef CLIENTSOCKET_H_
# define CLIENTSOCKET_H_

#include <boost/asio.hpp>
#include "Shared.h"
#include "Packet.hpp"

using boost::asio::ip::tcp;

class Client;

class ClientSocket
{
public:
    explicit ClientSocket(Client* client);

    bool Connect(std::string const& addr, std::string const& port);
    bool IsOpen() const;

    void HandleInput(boost::system::error_code const& error, std::size_t bytes_transferred);
    void SendPacket(Packet const* packet);

    void Close();

private:
    void _RegisterRead();

    tcp::socket _socket;
    Client*  _client;
    char header[PACKET_HEADER_SIZE];
};

#endif /* !CLIENTSOCKET_H_ */
