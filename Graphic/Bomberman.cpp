/*
** Bomberman.cpp for  in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:22 2013 fabien casters
** Last update Wed May 15 14:08:41 2013 vincent leroy
*/

#include <iostream>
#include "Bomberman.h"

Bomberman::Bomberman() :
    _cam(), _cube()
{
}

void Bomberman::initialize(void)
{
    window_.create();
    _cam.initialize();
    _cube.initialize();
}

void Bomberman::update(void)
{
    _cam.update(gameClock_, input_);
    _cube.update(gameClock_, input_);
}

void Bomberman::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
    glClearDepth(1.0f);

    _cube.draw();
    window_.display();
}

void Bomberman::unload(void)
{
}
