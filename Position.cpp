/*
** Position.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 17:32:36 2013 maxime ginters
** Last update Thu May 23 17:04:52 2013 maxime ginters
*/

#include "Position.h"
#include <cmath>

Position::Position() :
    _posX(0.0f), _posY(0.0f),
    _posZ(0.0f), _orr(0.0f),
    _speed(5.0f), _speed_or(1.0f),
    _movementFlags(0)
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

void Position::SetMovementFlags(uint32 flags)
{
    _movementFlags = flags;
}

bool Position::AddMovementFlag(uint32 flag)
{
    if (_movementFlags & flag)
        return false;
    _movementFlags |= flag;
    return true;
}

bool Position::RemoveMovementFlag(uint32 flag)
{
    if (!(_movementFlags & flag))
        return false;
    _movementFlags &= ~flag;
    return true;
}

bool Position::UpdateMovementFlag(uint32 flag, bool add)
{
    if (add)
        return AddMovementFlag(flag);
    else
        return RemoveMovementFlag(flag);
}

bool Position::HasMovementFlag(uint32 flag) const
{
    return (_movementFlags & flag);
}

void Position::SetSpeed(float speed)
{
    _speed = speed;
}

float Position::GetSpeed() const
{
    return _speed;
}

void Position::SetSpeedOr(float speed_or)
{
    _speed_or = speed_or;
}

float Position::GetSpeedOr() const
{
    return _speed_or;
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

uint32 Position::GetMovementFlags() const
{
    return _movementFlags;
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
