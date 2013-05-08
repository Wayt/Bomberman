/*
** Packet.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 08 17:23:17 2013 maxime ginters
** Last update Wed May 08 18:13:24 2013 maxime ginters
*/

#ifndef PACKET_H_
# define PACKET_H_

#include <vector>
#include "Opcodes.h"
#include "Shared.h"

#define PACKET_DEFAULT_SIZE 512

inline bool my_is_big_endian()
{
    int32 i = 1;
    int8* ptr = (int8*)&i;
    return *ptr == 1 ? false : true;
}

template<class T>
T swap_endian(T u)
{
    if (my_is_big_endian())
        return u;

    union
    {
        T u;
        int8 u8[sizeof(T)];
    } src, dest;

    src.u = u;

    for (size_t i = 0; i < sizeof(T); ++i)
        dest.u8[i] = src.u8[sizeof(T) - i - 1];

    return dest.u;
}

class Packet
{
public:
    Packet(Opcodes code, uint32 size = PACKET_DEFAULT_SIZE) :
        _rpos(0), _wpos(0)
    {
        _storage.reserve(size + 2);
        *this << uint16(code);
    }

    Packet& operator<<(uint8 value)
    {
        append<uint8>(value);
        return *this;
    }

    Packet& operator<<(uint16 value)
    {
        append<uint16>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(uint32 value)
    {
        append<uint32>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(uint64 value)
    {
        append<uint64>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(int8 value)
    {
        append<int8>(value);
        return *this;
    }

    Packet& operator<<(int16 value)
    {
        append<int16>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(int32 value)
    {
        append<int32>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(int64 value)
    {
        append<int64>(swap_endian(value));
        return *this;
    }

    size_t size() const
    {
        return _storage.size();
    }

    const uint8* content() const
    {
        return &_storage[0];
    }

private:
    template<class T>
    void append(T value)
    {
        append((uint8*)&value, sizeof(value));
    }

    void append(const uint8* data, size_t size)
    {
        if (_storage.size() < _wpos + size)
            _storage.resize(_wpos + size);
        memcpy(&_storage[_wpos], data, size);
        _wpos += size;
    }

    std::vector<uint8> _storage;
    uint32 _rpos;
    uint32 _wpos;
};

#endif /* !PACKET_H_ */
