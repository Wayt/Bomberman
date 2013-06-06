/*
** ClientSocket.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 13 14:26:06 2013 maxime ginters
** Last update Thu Jun 06 13:01:47 2013 maxime ginters
*/

#include <boost/bind.hpp>
#include "ClientSocket.h"
#include "Client.h"

ClientSocket::ClientSocket(Client* client) :
    _socket(client->GetIOService()), _client(client)
{

}

bool ClientSocket::Connect(std::string const& addr, std::string const& port)
{
    tcp::resolver resolver(_socket.get_io_service());
    tcp::resolver::query query(tcp::v4(), addr, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    try
    {
        boost::asio::connect(_socket, iterator);
        boost::asio::ip::tcp::no_delay option(true);
        _socket.set_option(option);
        size_t size = _socket.available();
        if (size > 0)
        {
            uint8 buff[size];
            boost::system::error_code ignored_ec;
            read(_socket, boost::asio::buffer(buff, size), ignored_ec);
        }
    }
    catch (boost::system::system_error& e)
    {
        sLog->error("Error: %s", e.what());
        return false;
    }
    _RegisterRead();
    return true;
}

bool ClientSocket::IsOpen() const
{
    return _socket.is_open();
}

void ClientSocket::HandleInput(boost::system::error_code const& error, std::size_t bytes_transferred)
{
    if (error)
    {
        sLog->error("Error: %s", error.message().c_str());
        if (_client)
            _client->Stop();
        return;
    }

    if (!_client)
        return;

    (void)bytes_transferred;
    uint16 size = swap_endian(*((uint16 const*)&header[0]));
    uint8 buff[size];

    boost::system::error_code ignored_ec;
    read(_socket, boost::asio::buffer(buff, size), ignored_ec);

    Packet* pkt = new Packet(buff, size);
    if (pkt->GetOpcode() == SMSG_PONG)
    {
        _client->HandleReceivPong();
        delete pkt;
    }
    else
        _client->QueuePacket(pkt);
    _RegisterRead();
}

void ClientSocket::SendPacket(Packet const* packet)
{
    write(_socket, boost::asio::buffer(packet->content(), packet->size()));
}

void ClientSocket::Close()
{
    _socket.close();
}

void ClientSocket::_RegisterRead()
{
    async_read(_socket, boost::asio::buffer(header, PACKET_HEADER_SIZE),
            boost::bind(&ClientSocket::HandleInput, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}
