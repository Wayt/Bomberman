/*
** Model.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Wed May 15 18:35:35 2013 fabien casters
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "Model.h"
#include "ClientObject.h"

Model::Model(ClientObject const *o) :
    _object(o)
{
}

void Model::draw()
{
    float size = 5.0f;
    float x, y;
    _object->GetPosition(x, y);

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.75f);

    glVertex3f(x - size / 2, y - size / 2.f, 0);
    glVertex3f(x - size / 2, y + size / 2.f, 0);
    glVertex3f(x - size / 2, y + size / 2.f, size);
    glVertex3f(x - size / 2, y - size / 2.f, size);

    glVertex3f(x - size / 2, y - size / 2.f, 0);
    glVertex3f(x - size / 2, y + size / 2.f, 0);
    glVertex3f(x + size / 2, y + size / 2.f, 0);
    glVertex3f(x + size / 2, y - size / 2.f, 0);

    glVertex3f(x - size / 2, y + size / 2.f, 0);
    glVertex3f(x + size / 2, y + size / 2.f, 0);
    glVertex3f(x + size / 2, y + size / 2.f, size);
    glVertex3f(x - size / 2, y + size / 2.f, size);

    glVertex3f(x - size / 2, y - size / 2.f, 0);
    glVertex3f(x + size / 2, y - size / 2.f, 0);
    glVertex3f(x + size / 2, y - size / 2.f, size);
    glVertex3f(x - size / 2, y - size / 2.f, size);

    glVertex3f(x - size / 2, y - size / 2.f, size);
    glVertex3f(x - size / 2, y + size / 2.f, size);
    glVertex3f(x + size / 2, y + size / 2.f, size);
    glVertex3f(x + size / 2, y - size / 2.f, size);

    glVertex3f(x + size / 2, y - size / 2.f, 0);
    glVertex3f(x + size / 2, y + size / 2.f, 0);
    glVertex3f(x + size / 2, y + size / 2.f, size);
    glVertex3f(x + size / 2, y - size / 2.f, size);

    glEnd();
}
