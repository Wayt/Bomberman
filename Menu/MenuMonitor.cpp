/*
** MenuMonitor.cpp for  in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:22 2013 fabien casters
** Last update Wed May 15 16:13:32 2013 fabien casters
*/

#include <iostream>
#include <unistd.h>
#include "MenuMonitor.h"

MenuMonitor::MenuMonitor(Client *cli, uint32 width, uint32 height) :
    _client(cli), _width(width), _height(height), _cam(), _menu(0, 0, -100, 0)
{
}

void MenuMonitor::initialize(void)
{
    window_.create();
    _cam.initialize();
    _menu.initialize();
}

void MenuMonitor::update(void)
{
    _cam.update(gameClock_, input_);
    _menu.update(gameClock_, input_);
    ::usleep(1000);
}

void MenuMonitor::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
    glClearDepth(1.0f);
    _menu.draw();
    window_.display();
}

void MenuMonitor::unload(void)
{
}
