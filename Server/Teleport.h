/*
** Teleport.h for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 22:15:39 2013 vincent leroy
** Last update Wed Jun 05 22:16:38 2013 vincent leroy
*/

#ifndef TELEPORT_H_
# define TELEPORT_H_

#include "Object.h"

class Teleport : public Object
{
public:
    Teleport(uint64 guid);
    virtual ~Teleport();
};

#endif /* !TELEPORT_H_ */
