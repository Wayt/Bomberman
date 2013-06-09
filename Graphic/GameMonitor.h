/*
** GameMonitor.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:32 2013 fabien casters
** Last update Sun Jun 09 16:20:27 2013 vincent leroy
*/

#ifndef GAMEMONITOR_H_
# define GAMEMONITOR_H_

#include <vector>
#include "Camera.h"
#include "GraphicObject.h"
#include "Game.hpp"
#include "Shared.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Client;

class GameMonitor : public gdl::Game
{
public:
    GameMonitor(Client* cli, uint32 width, uint32 height);

    void initialize();
    void update();
    void draw();
    void unload();

    void getKeyVector(std::vector<bool>& vec) const;

    void Close();

private:

    Client* _client;
    uint32 _width;
    uint32 _height;
    Camera _cam;
    std::vector<bool> _keyVector;
};

#endif
