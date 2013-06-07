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
    InputBox *ib;

    single->addBox("config", SelectBox::INPUTBOX);
    (*single)["config"]->setTexture("Menu/images/input_name.png");
    if ((ib = dynamic_cast<InputBox *>((*single)["config"])) != NULL)
	ib->addInput("name", 380, 285, 28, gdl::Color(0, 255, 0, 255));
    single->addBox("new", SelectBox::CHECKBOX);
    single->addBox("load", SelectBox::CHECKBOX);
    (*single)["new"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");
    (*single)["load"]->setTexture("Menu/images/load_game.png", "Menu/images/load_game.png");
    single->addBackBox("Menu/images/back.png");

    SubMenu *create = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    create->addBox("config", SelectBox::INPUTBOX);
    (*create)["config"]->setTexture("Menu/images/new.png");
    if ((ib = dynamic_cast<InputBox *>((*create)["config"])) != NULL){
	ib->addInput("name", 230, 250, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("x", 230, 280, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("y", 230, 310, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("bot", 230, 340, 25, gdl::Color(0, 255, 0, 255));
    }
    create->addBox("start", SelectBox::CHECKBOX);
    (*create)["start"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");
    create->addBackBox("Menu/images/back.png");

    SubMenu *join = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    join->addBox("config", SelectBox::INPUTBOX);
    (*join)["config"]->setTexture("Menu/images/new.png");
    if ((ib = dynamic_cast<InputBox *>((*join)["config"])) != NULL){
	ib->addInput("name", 230, 250, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("ip", 230, 280, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("port", 230, 310, 25, gdl::Color(0, 255, 0, 255));
    }
    join->addBox("start", SelectBox::CHECKBOX);
    (*join)["start"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");
    join->addBackBox("Menu/images/back.png");

    SubMenu *multi = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    multi->addBox("create", "Menu/images/create_server.png", create);
    multi->addBox("join", "Menu/images/join_server.png", join);
    multi->addBackBox("Menu/images/back.png");

    menu_.addBox("single", "Menu/images/single.png", single);
    menu_.addBox("multi", "Menu/images/multi.png", multi);
    menu_.addBox("highscore", SelectBox::CHECKBOX);
    menu_.addBox("credits", SelectBox::CHECKBOX);
    menu_["highscore"]->setTexture("Menu/images/highscore.png", "Menu/images/highscore.png");
    menu_["credits"]->setTexture("Menu/images/credits.png", "Menu/images/credits.png");
    menu_.addBackBox("Menu/images/back.png");

    menu_.setStatus(SubObject::VISIBLE);
}

void Menu::initialize()
{
    menu_.initialize();
}

void Menu::update(gdl::GameClock const &clock, gdl::Input &input)
{ 
    InputBox *box;

    if ((*menu_["single"])["new"]->value()  == 1){
	if ((box = dynamic_cast<InputBox*>((*menu_["single"])["config"])) != NULL)
	    startSolo(box);
	(*menu_["single"])["new"]->select();
    }
    if ((*(*menu_["multi"])["create"])["start"]->value() == 1){
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["create"])["config"])) != NULL)
	    createServer(box);
	(*(*menu_["multi"])["create"])["start"]->select();
    }
    if ((*(*menu_["multi"])["join"])["start"]->value() == 1){
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["join"])["config"])) != NULL)
	    joinServer(box);
	(*(*menu_["multi"])["join"])["start"]->select();
    }
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
