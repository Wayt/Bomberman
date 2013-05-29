/*
** Position.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 17:32:36 2013 maxime ginters
** Last update Wed May 29 14:03:03 2013 maxime ginters
*/

#include "Position.h"
#include <cmath>

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

void Position::GetPosition(Position& pos) const
{
    GetPosition(pos._posX, pos._posY, pos._posZ, pos._orr);
}

void Position::UpdateOrientation(float o)
{
    _orr = o;
}

void Position::UpdatePosition(float x, float y, float z, float o)
{
    _posX = x;
    _posY = y;
    _posZ = z;
    _orr = o;
}

void Position::UpdatePosition(float x, float y, float o)
{
    UpdatePosition(x, y, _posZ, o);
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

float Position::GetDistance2d(Position const* other) const
{
    return GetDistance2d(this, other);
}

float Position::GetDistance2d(Position const* pos1, Position const* pos2)
{
    float x1, y1, x2, y2;
    pos1->GetPosition(x1, y1);
    pos2->GetPosition(x2, y2);
    return GetDistance2d(x1, y1, x2, y2);
}

float Position::GetDistance2d(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

float Position::GetDistance2dSquare(Position const* other) const
{
    return GetDistance2d(this, other);
}

float Position::GetDistance2dSquare(Position const* pos1, Position const* pos2)
{
    float x1, y1, x2, y2;
    pos1->GetPosition(x1, y1);
    pos2->GetPosition(x2, y2);
    return GetDistance2d(x1, y1, x2, y2);
}

float Position::GetDistance2dSquare(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (dx * dx + dy * dy);
}

std::ostream& operator<<(std::ostream& stream, Position const& pos)
{
    stream << "X : " << pos.GetPositionX() << " - Y : " << pos.GetPositionY() << " - Z : " << pos.GetPositionZ() << " - O : " << pos.GetOrientation();
    return stream;
}

void Position::HandlePositionChange()
{
}

void Position::GetXYAt(float range, float angle, float& destx, float& desty) const
{
    angle += _orr;

    destx = _posX + range * cos(angle);
    desty = _posY + range * sin(angle);
}
