/*
** MovementIdle.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:26:03 2013 maxime ginters
** Last update Thu May 16 19:20:04 2013 vincent leroy
*/

#ifndef MOVEMENTILDE_H_
# define MOVEMENTILDE_H_

#include "MotionMaster.hpp"

class MovementIdle : public AMovement
{
public:
    MovementIdle(Position* obj);

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes newType);
};

#endif /* !MOVEMENTILDE_H_ */
