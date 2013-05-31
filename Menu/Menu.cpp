//
// Menu.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Thu May 16 11:01:51 2013 
// Last update Thu May 16 11:01:51 2013 
//

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "Menu.h"
#include "Image.hpp"
#include "CheckBox.h"

Menu::Menu(float x, float y, float z, float o) :
    AObject(x, y, z, o), menu_(_pos.x, _pos.y, _pos.z, _rot.x)
{

    SubMenu *m1 = new SubMenu(x, y, z, o);
    m1->addBox("images/settings.png", "images/new_game.png");
    m1->addBox("images/settings.png", "images/new_game.png");
    m1->addBox("images/settings.png", "images/new_game.png");
    m1->addBackBox("images/quit.png");
    //m1->setMovableH();

    menu_.addBox("images/new_game.png", m1);
    menu_.addBox("images/settings.png", "images/new_game.png");
    menu_.addBackBox("images/quit.png");

}

void Menu::initialize()
{
    menu_.initialize();
}

void Menu::update(gdl::GameClock const &clock, gdl::Input &input)
{ 
    usleep(1000);
    menu_.update(clock, input);
    if (menu_.getRet() == false)
	::exit(0);
}

void Menu::draw()
{
    menu_.draw();
}

Menu::~Menu()
{
}
