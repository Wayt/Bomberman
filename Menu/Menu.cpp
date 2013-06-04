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

    SubMenu *single= new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    single->addBox("new", SelectBox::CHECKBOX);
    single->addBox("load", SelectBox::CHECKBOX);
    (*single)["new"]->setTexture("images/new.png", "images/new.png");
    (*single)["load"]->setTexture("images/load.png", "images/load.png");
    single->addBackBox("images/back.png");

    SubMenu *multi = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    multi->addBox("create", SelectBox::CHECKBOX);
    multi->addBox("join", SelectBox::CHECKBOX);
    (*multi)["create"]->setTexture("images/create.png", "images/create.png");
    (*multi)["join"]->setTexture("images/join.png", "images/join.png");
    multi->addBackBox("images/back.png");

    menu_.addBox("single", "images/single.png", single);
    menu_.addBox("multi", "images/multi.png", multi);
    menu_.addBox("highscore", SelectBox::CHECKBOX);
    menu_.addBox("credits", SelectBox::CHECKBOX);
    menu_["highscore"]->setTexture("images/highscore.png", "images/highscore.png");
    menu_["credits"]->setTexture("images/credits.png", "images/credits.png");
    menu_.addBackBox("images/quit.png");


}

void Menu::initialize()
{
    menu_.initialize();
}

void Menu::update(gdl::GameClock const &clock, gdl::Input &input)
{ 
    if ((*menu_["single"])["new"]->value()  == 1)
	std::cout << "game started" << std::endl;
    menu_.update(clock, input);
    if (menu_.getRet() == false)
	::exit(0);
    usleep(1000);
}

void Menu::draw()
{
    menu_.draw();
}

Menu::~Menu()
{
}
