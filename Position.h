/*
** Position.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 17:31:54 2013 maxime ginters
** Last update Wed May 15 12:16:40 2013 maxime ginters
*/

#ifndef POSITION_H_
# define POSITION_H_

#include <ostream>
#include "Packet.hpp"

class Position
{
public:
    Position();

    float GetPositionX() const;
    float GetPositionY() const;
    float GetPositionZ() const;
    float GetOrientation() const;
    void GetPosition(float& x, float& y) const;
    void GetPosition(float& x, float& y, float& z) const;
    void GetPosition(float& x, float& y, float& z, float& o) const;
    Position const* GetPosition() const;
    void UpdatePosition(float x, float y, float z, float o);

    void ReadPosition(Packet& data);
    void WritePosition(Packet& data) const;

    float GetDistance2d(Position const* other) const;

    static float GetDistance2d(Position const* pos1, Position const* pos2);
    static float GetDistance2d(float x1, float y1, float x2, float y2);
private:
    float _posX;
    float _posY;
    float _posZ;
    float _orr;
};

std::ostream& operator<<(std::ostream& stream, Position const& pos);

#endif /* !POSITION_H_ */
