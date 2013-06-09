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

#define MAP_MIN_X 10
#define MAP_MIN_Y 10
#define DEFAULT_TIME 60

#include "SubObject.h"
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

    void startSolo(InputBox *box, KeysMap);
    void joinServer(InputBox *box, KeysMap);
    void createServer(InputBox *box, KeysMap);
    void startWithMap(InputBox *name, InputBox *map, KeysMap);

private:
    bool	initm_;
    Client* 	_client;
    uint32 	_width;
    uint32 	_height;
    MenuCamera 	_cam;
    Menu	_menu;
    SelectBox 	_background;
};

#endif
