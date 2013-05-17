/*
** MovementPlayer.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:19 2013 maxime ginters
** Last update Thu May 16 21:39:44 2013 vincent leroy
*/

#ifndef MOVEMENTPLAYER_H_
# define MOVEMENTPLAYER_H_

#include "MotionMaster.hpp"

class MovementPlayer : public AMovement
{
public:
    MovementPlayer(Position* obj);

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes newType);

private:
    float getAngle() const;
};

#endif /* !MOVEMENTPLAYER_H_ */
