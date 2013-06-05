/*
** Range.h for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Jun 05 19:27:36 2013 vincent leroy
** Last update Wed Jun 05 19:29:31 2013 vincent leroy
*/

#ifndef RANGE_H_
# define RANGE_H_

#include "Object.h"

class Range : public Object
{
public:
    Range(uint64 guid);
    virtual ~Range();
};

#endif /* !RANGE_H_ */
