/*
** Vector.cpp for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Fri May 10 13:42:06 2013 fabien casters
** Last update Wed May 15 13:44:13 2013 vincent leroy
*/

#include "Vector.h"

Vector::Vector(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
{
}

Vector::Vector() :
    x(0.0f), y(0.0f), z(0.0f)
{
}
