/*
** MenuMonitor.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:32 2013 fabien casters
** Last update Wed May 15 16:13:32 2013 fabien casters
*/

#ifndef MENUMONITOR_H_
# define MENUMONITOR_H_

#include "MenuCamera.h"
#include "Game.hpp"
#include "Shared.h"
#include "SelectBox.h"
#include "Menu.h"


class Client;

class MenuMonitor : public gdl::Game
{
public:
    MenuMonitor(Client* cli, uint32 width, uint32 height);

    void initialize();
    void update();
    void draw();
    void unload();

private:
    Client* 	_client;
    uint32 	_width;
    uint32 	_height;
    MenuCamera 	_cam;
    Menu	_menu;
};

#endif
