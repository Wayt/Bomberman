/*
** Speed.h for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 18:36:32 2013 vincent leroy
** Last update Wed Jun 05 18:40:32 2013 vincent leroy
*/

#ifndef SPEED_H_
# define SPEED_H_

#include "Object.h"

class Speed : public Object
{
public:
    Speed(uint64 guid);
    virtual ~Speed();
};

#endif /* !SPEED_H_ */
