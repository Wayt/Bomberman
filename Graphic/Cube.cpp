/*
** Cube.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Wed May 15 17:47:36 2013 fabien casters
*/

#include "Cube.h"

Cube::Cube(float x, float y, float z, float o) :
    AObject(x, y, z, o)
{
}

void Cube::initialize()
{
}

void Cube::update(gdl::GameClock const&, gdl::Input &)
{
}

void Cube::draw()
{
    float size = 5.0f;

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.75f);

    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, 0);
    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, size);
    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, size);

    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, 0);
    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, 0);

    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, size);
    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, size);

    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, size);
    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, size);

    glVertex3f(_pos.x - size / 2, _pos.y - size / 2.f, size);
    glVertex3f(_pos.x - size / 2, _pos.y + size / 2.f, size);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, size);
    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, size);

    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, 0);
    glVertex3f(_pos.x + size / 2, _pos.y + size / 2.f, size);
    glVertex3f(_pos.x + size / 2, _pos.y - size / 2.f, size);

    glEnd();
}
