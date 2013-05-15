/*
** Cube.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Wed May 15 14:17:07 2013 vincent leroy
*/

#include "Cube.h"

Cube::Cube()
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
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0); // Rouge
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    glColor3ub(0, 0, 255); // Bleu
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    glColor3ub(0, 255, 0); // Vert
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();
    return ;

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.75f);

    glVertex3f(-150.0f, 150.0f, 150.0f);
    glVertex3f(-150.0f, -150.0f, 150.0f);
    glVertex3f(150.0f, -150.0f, 150.0f);
    glVertex3f(150.0f, 150.0f, 150.0f);

    glVertex3f(-150.0f, 150.0f, -150.0f);
    glVertex3f(-150.0f, -150.0f, -150.0f);
    glVertex3f(-150.0f, -150.0f, 150.0f);
    glVertex3f(-150.0f, 150.0f, 150.0f);

    glVertex3f(150.0f, 150.0f, -150.0f);
    glVertex3f(150.0f, -150.0f, -150.0f);
    glVertex3f(-150.0f, -150.0f, -150.0f);
    glVertex3f(-150.0f, 150.0f, -150.0f);

    glVertex3f(150.0f, 150.0f, 150.0f);
    glVertex3f(150.0f, -150.0f, 150.0f);
    glVertex3f(150.0f, -150.0f, -150.0f);
    glVertex3f(150.0f, 150.0f, -150.0f);

    glEnd();
}
