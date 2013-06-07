/*
** MenuCamera.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Fri May 10 13:47:18 2013 fabien casters
** Last update Wed May 15 13:15:33 2013 fabien casters
*/

#ifndef MENUCAMERA_H_
# define MENUCAMERA_H_

#include "GameClock.hpp"
#include "Input.hpp"
#include "Vector.h"

class MenuCamera
{
public:
    MenuCamera();
    void initialize();
    void update(gdl::GameClock const &, gdl::Input &);
private:
    Vector _pos;
    Vector _rot;
};

#endif
