/*
** GameMonitor.cpp for  in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:22 2013 fabien casters
** Last update Wed May 15 17:48:18 2013 fabien casters
*/

#include <iostream>
#include "GameMonitor.h"
#include "Client.h"

GameMonitor::GameMonitor(Client *cli, uint32 width, uint32 height) :
    _client(cli), _width(width), _height(height), _cam(), _cube(34.0f, 12.0f, 0.0f, 0.0f)
{
}

void GameMonitor::initialize(void)
{
    window_.create();
    _cam.initialize();
    _cube.initialize();
}

void GameMonitor::update(void)
{
    _cam.update(gameClock_, input_);
    _cube.update(gameClock_, input_);
}

void GameMonitor::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
    glClearDepth(1.0f);

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

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 255); // Bleu
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, _height, 0.0f);
    glVertex3f(_width, _height, 0.0f);
    glVertex3f(_width, 0.0f, 0.0f);
    glEnd();

    std::map<uint64, ClientObject *> const &map = _client->GetObjectMap();
    std::map<uint64, ClientObject *>::const_iterator iter;
    for(iter = map.begin(); iter != map.end(); ++iter)
    {
        float x, y, z, o;
        iter->second->GetPosition(x, y, z, o);
        Cube c(x, y, z, o);
        c.draw();
    }
    window_.display();
}

void GameMonitor::unload(void)
{
}
