/*
** Camera.cpp for  in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 15 12:59:41 2013 fabien casters
** Last update Tue Jun 04 14:56:51 2013 maxime ginters
*/

#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>

Camera::Camera() :
    _pos(0, -70.0f, 30.0f), _rot(0.0f, 0.0f, 0.0f)
{

}

void Camera::initialize()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 1.0f, 3000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Camera::update(ClientObjectPtr player)
{
    if (!player.get())
        return;
    float x, y;
    player->GetXYAt(10.0f, M_PI, x, y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, 20.0f, player->GetPositionX(), player->GetPositionY(), 0.0f, 0.0f, 0.0f, 1.0f);
}
