/*
** MenuCamera.cpp for  in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 15 12:59:41 2013 fabien casters
** Last update Wed May 15 15:42:21 2013 fabien casters
*/

#include "MenuCamera.h"
#include <GL/gl.h>
#include <GL/glu.h>

MenuCamera::MenuCamera() :
    _pos(50.0f, 160.0f, 400.0f), _rot(0.0f, 0.0f, 0.0f)
{

}

void MenuCamera::initialize()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 3000.0f);
    gluLookAt(_pos.x, _pos.y, _pos.z, 50.0f, 160.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void MenuCamera::update(gdl::GameClock const &, gdl::Input &)
{
}
