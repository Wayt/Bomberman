/*
** AObject.h for  in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 15 13:22:32 2013 fabien casters
** Last update Wed May 15 13:28:16 2013 fabien casters
*/

#ifndef AOBJECT_H_
# define AOBJECT_H_

#include "Vector.h"
#include "GameClock.h"
#include "Input.h"

class AObject
{
public:
    AObject() {}
    virtual void initialize() = 0;
    virtual void update(gdl::GameClock const &, gdl::Input &) = 0;
    virtual void draw() = 0;
private:
    Vector _pos;
    Vector _rot;
};

#endif

