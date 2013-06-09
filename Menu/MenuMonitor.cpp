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

MenuMonitor::MenuMonitor(Client *cli, uint32 width, uint32 height) : initm_(false),
    _client(cli), _width(width), _height(height), _cam(), _menu(0, 0, -100, 0), _background(-300, -330, -400, 0)
{
    _background.setTexture("Menu/images/background.png");
    _background.setStatus(SubObject::VISIBLE);
}

void MenuMonitor::initialize(void)
{
    window_.create();
    _cam.initialize();
    if (!initm_){
	_menu.initialize();
	initm_ = true;
    }
    _background.initialize();
}

void MenuMonitor::update(void)
{
    ::usleep(1000);
    _cam.update(gameClock_, input_);
    _menu.update(gameClock_, input_);
    _background.update(gameClock_, input_);
    SubMenu &menu_ = _menu.getMenu();


    InputBox *box;
    InputBox *map;
    KeysMap keymap;

    keymap = (*menu_["settings"])["keymap"]->value() ? KEYMAP_FR : KEYMAP_US;
    if ((*menu_["single"])["new"]->value()  == 1){
	if ((box = dynamic_cast<InputBox*>((*menu_["single"])["config"])) != NULL)
	    startSolo(box, keymap);
	(*menu_["single"])["new"]->select();
    }
    if ((*(*menu_["multi"])["create"])["start"]->value() == 1){
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["create"])["config"])) != NULL)
	    createServer(box, keymap);
	(*(*menu_["multi"])["create"])["start"]->select();
    }
    if ((*(*menu_["multi"])["join"])["start"]->value() == 1){
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["join"])["config"])) != NULL)
	    joinServer(box, keymap);
	(*(*menu_["multi"])["join"])["start"]->select();
    }
    if ((*(*menu_["single"])["load"])["start"]->value() == 1){
	if (((map = dynamic_cast<InputBox*>((*(*menu_["single"])["load"])["map"])) != NULL) &&
		((box = dynamic_cast<InputBox*>((*menu_["single"])["config"])) != NULL))
	    startWithMap(box, map, keymap);
	(*(*menu_["single"])["load"])["start"]->select();
    }
    if (menu_.getRet() == false){
	unload();
    }
}

void MenuMonitor::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
    glClearDepth(1.0f);
    _menu.draw();
    _background.draw();
    window_.display();
}

void MenuMonitor::unload(void)
{
	window_.close();
}
