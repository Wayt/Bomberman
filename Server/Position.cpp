/*
** Position.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 17:32:36 2013 maxime ginters
** Last update Tue May 14 17:43:51 2013 maxime ginters
*/

#include "Position.h"

Position::Position() :
    _posX(0.0f), _posY(0.0f),
    _posZ(0.0f), _orr(0.0f)
{}


float Position::GetPositionX() const
{
    return _posX;
}

float Position::GetPositionY() const
{
    return _posY;
}

float Position::GetPositionZ() const
{
    return _posZ;
}

float Position::GetOrientation() const
{
    return _orr;
}

void Position::GetPosition(float& x, float& y) const
{
    x = _posX;
    y = _posY;
}

void Position::GetPosition(float& x, float& y, float& z) const
{
    x = _posX;
    y = _posY;
    z = _posZ;
}

void Position::GetPosition(float& x, float& y, float& z, float& o) const
{
    x = _posX;
    y = _posY;
    z = _posZ;
    o = _orr;
}

Position const* Position::GetPosition() const
{
    return this;
}

void Position::UpdatePosition(float x, float y, float z, float o)
{
    _posX = x;
    _posY = y;
    _posZ = z;
    _orr = o;
}

void Position::ReadPosition(Packet& data)
{
    data >> _posX;
    data >> _posY;
    data >> _posZ;
    data >> _orr;
}

void Position::WritePosition(Packet& data) const
{
    data << float(_posX);
    data << float(_posY);
    data << float(_posZ);
    data << float(_orr);
}

std::ostream& operator<<(std::ostream& stream, Position const& pos)
{
    stream << "X : " << pos.GetPositionX() << " - Y : " << pos.GetPositionY() << " - Z : " << pos.GetPositionZ() << " - O : " << pos.GetOrientation();
    return stream;
}
