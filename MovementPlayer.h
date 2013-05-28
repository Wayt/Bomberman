/*
** MovementPlayer.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:19 2013 maxime ginters
** Last update Tue May 28 18:42:20 2013 vincent leroy
*/

#ifndef MOVEMENTPLAYER_H_
# define MOVEMENTPLAYER_H_

#include "MotionMaster.hpp"

class MovementPlayer : public AMovement
{
public:
    MovementPlayer(GameObject* obj);

    void Initialize();
    void Update(uint32 const diff);
    void Finish();
    void Abort(MovementTypes newType);
};

#endif /* !MOVEMENTPLAYER_H_ */
