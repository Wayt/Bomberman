/*
** Bomb.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 18 13:40:51 2013 maxime ginters
** Last update Wed Jun 05 22:23:40 2013 maxime ginters
*/

#ifndef BOMB_H_
# define BOMB_H_

#include "Object.h"

#define BOMB_RANGE 10

class Bomb : public Object
{
public:
    explicit Bomb(uint64 guid, MapObject* owner);

    void DoAction(uint32 id);

    void HandleExplode();

    void Despawn();

private:
};

#endif /* !BOMB_H_ */
