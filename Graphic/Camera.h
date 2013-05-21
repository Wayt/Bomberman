/*
** Camera.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Fri May 10 13:47:18 2013 fabien casters
** Last update Tue May 21 15:22:17 2013 fabien casters
*/

#ifndef CAMERA_H_
# define CAMERA_H_

#include "GameClock.hpp"
#include "Input.hpp"
#include "Vector.h"
#include "ClientObject.h"

class Camera
{
public:
    Camera();
    void initialize();
    void update(ClientObjectPtr);
private:
    Vector _pos;
    Vector _rot;
};

#endif
