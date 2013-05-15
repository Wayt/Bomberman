/*
** MovementIdle.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:26:03 2013 maxime ginters
** Last update Wed May 15 13:52:55 2013 maxime ginters
*/

#ifndef MOVEMENTILDE_H_
# define MOVEMENTILDE_H_

#include "MotionMaster.hpp"

class MovementIdle : public AMovement
{
public:
    MovementIdle(MapObject* obj);

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes newType);
};

#endif /* !MOVEMENTILDE_H_ */
