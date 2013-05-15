/*
** AObject.h for  in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 15 13:22:32 2013 fabien casters
** Last update Wed May 15 14:33:35 2013 vincent leroy
*/

#ifndef AOBJECT_H_
# define AOBJECT_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector.h"
#include "GameClock.hpp"
#include "Input.hpp"

class AObject
{
public:
    AObject(float x, float y, float z, float orr)
    {
        _pos.x = x;
        _pos.y = y;
        _pos.z = z;

        _rot.x = orr;
        _rot.y = orr;
        _rot.z = 0.0f;
    }

    virtual void initialize() = 0;
    virtual void update(gdl::GameClock const &, gdl::Input &) = 0;
    virtual void draw() = 0;

private:
    Vector _pos;
    Vector _rot;
};

#endif

