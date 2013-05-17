/*
** Position.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 17:31:54 2013 maxime ginters
** Last update Fri May 17 18:14:26 2013 maxime ginters
*/

#ifndef POSITION_H_
# define POSITION_H_

#include <ostream>
#include "Packet.hpp"

enum MovementFlags
{
    MOVEMENT_NONE       = 0x00000000,
    MOVEMENT_FORWARD    = 0x00000001,
    MOVEMENT_BACKWARD   = 0x00000002,
    MOVEMENT_TURN_LEFT  = 0x00000004,
    MOVEMENT_TURN_RIGHT = 0x00000008,
    MOVEMENT_STRAF_LEFT = 0x00000010,
    MOVEMENT_STRAF_RIGHT= 0x00000020,

    MOVEMENT_MOVING     = (MOVEMENT_FORWARD | MOVEMENT_BACKWARD | \
                            MOVEMENT_STRAF_LEFT | MOVEMENT_STRAF_RIGHT),
};

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
    void UpdatePosition(float x, float y, float o);

    virtual void HandlePositionChange();

    void ReadPosition(Packet& data);
    void WritePosition(Packet& data) const;

    float GetDistance2d(Position const* other) const;

    uint32 GetMovementFlags() const;
    void SetMovementFlags(uint32 flags);
    bool AddMovementFlag(uint32 flag);
    bool RemoveMovementFlag(uint32 flag);
    bool UpdateMovementFlag(uint32 flag, bool add);
    bool HasMovementFlag(uint32 flag) const;

    void SetSpeed(float speed);
    float GetSpeed() const;
    void SetSpeedOr(float speed_or);
    float GetSpeedOr() const;

    static float GetDistance2d(Position const* pos1, Position const* pos2);
    static float GetDistance2d(float x1, float y1, float x2, float y2);

private:
    float _posX;
    float _posY;
    float _posZ;
    float _orr;
    float _speed;
    float _speed_or;
    uint32 _movementFlags;
};

std::ostream& operator<<(std::ostream& stream, Position const& pos);

#endif /* !POSITION_H_ */
