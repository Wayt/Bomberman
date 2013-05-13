/*
** Packet.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 08 17:23:17 2013 maxime ginters
** Last update Mon May 13 13:44:42 2013 maxime ginters
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
        _rpos(2), _wpos(2)
    {
        _storage.reserve(size + 4);
        *this << uint16(code);
    }

    Packet(char buff[], uint16 size) :
        _rpos(4), _wpos(size)
    {
        _storage.reserve(size + 2);
        memcpy(&_storage[0], (const uint8*)&size, 2);
        memcpy(&_storage[2], buff, size);
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

    Packet& operator<<(float value)
    {
        append<float>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(double value)
    {
        append<double>(swap_endian(value));
        return *this;
    }

    Packet& operator<<(std::string const& value)
    {
        append((uint8 const*)value.c_str(), value.length());
        append((uint8)0);
        return *this;
    }

    Packet& operator>>(std::string& value)
    {
        value.clear();
        while (_rpos < size())
        {
            char c = read<char>();
            if (c == 0)
                break;
            value += c;
        }
        return *this;
    }

    Packet& operator>>(uint8& value)
    {
        value = read<uint8>();
        return *this;
    }

    Packet& operator>>(uint16& value)
    {
        value = read<uint16>();
        return *this;
    }

    Packet& operator>>(uint32& value)
    {
        value = read<uint32>();
        return *this;
    }

    Packet& operator>>(uint64& value)
    {
        value = read<uint64>();
        return *this;
    }

    Packet& operator>>(int8& value)
    {
        value = read<int8>();
        return *this;
    }

    Packet& operator>>(int16& value)
    {
        value = read<int16>();
        return *this;
    }

    Packet& operator>>(int32& value)
    {
        value = read<int32>();
        return *this;
    }

    Packet& operator>>(int64& value)
    {
        value = read<int64>();
        return *this;
    }

    Packet& operator>>(float& value)
    {
        value = read<float>();
        return *this;
    }

    Packet& operator>>(double& value)
    {
        value = read<double>();
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

    Opcodes GetOpcode() const
    {
        return (Opcodes)read<uint16>(0);
    }

private:
    template<class T>
    void append(T value)
    {
        append((uint8*)&value, sizeof(value));
    }

    void append(const uint8* data, uint32 size)
    {
        if (_storage.size() < _wpos + size)
            _storage.resize(_wpos + size);
        memcpy(&_storage[_wpos], data, size);
        _wpos += size;
        update_size();
    }

    void update_size()
    {
        uint16 size = _wpos - 2;
        memcpy(&_storage[0], (const uint8*)&size, 2);
    }

    template<class T>
    T read()
    {
        T val = read<T>(_rpos);
        _rpos += sizeof(T);
        return val;
    }

    template<class T>
    T read(uint32 pos) const
    {
        T val = *((T const*)&_storage[pos]);
        return val;
    }

    std::vector<uint8> _storage;
    uint16 _rpos;
    uint16 _wpos;
};

#endif /* !PACKET_H_ */
