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
    (*single)["config"]->setTexture("images/new.png");
    if ((ib = dynamic_cast<InputBox *>((*single)["config"])) != NULL)
	ib->addInput("name", 230, 250, 25, gdl::Color(0, 255, 0, 255));
    single->addBox("new", SelectBox::CHECKBOX);
    single->addBox("load", SelectBox::CHECKBOX);
    (*single)["new"]->setTexture("images/new.png", "images/new.png");
    (*single)["load"]->setTexture("images/load.png", "images/load.png");
    single->addBackBox("images/back.png");

    SubMenu *create = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    create->addBox("config", SelectBox::INPUTBOX);
    (*create)["config"]->setTexture("images/new.png");
    if ((ib = dynamic_cast<InputBox *>((*create)["config"])) != NULL){
	ib->addInput("name", 230, 250, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("x", 230, 280, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("y", 230, 310, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("bot", 230, 340, 25, gdl::Color(0, 255, 0, 255));
    }
    create->addBox("start", SelectBox::CHECKBOX);
    (*create)["start"]->setTexture("images/new_game.png", "images/new_game.png");
    create->addBackBox("images/back.png");

    SubMenu *join = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    join->addBox("config", SelectBox::INPUTBOX);
    (*join)["config"]->setTexture("images/new.png");
    if ((ib = dynamic_cast<InputBox *>((*join)["config"])) != NULL){
	ib->addInput("name", 230, 250, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("ip", 230, 280, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("port", 230, 310, 25, gdl::Color(0, 255, 0, 255));
    }
    join->addBox("start", SelectBox::CHECKBOX);
    (*join)["start"]->setTexture("images/new_game.png", "images/new_game.png");
    join->addBackBox("images/back.png");

    SubMenu *multi = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    multi->addBox("create", "images/create.png", create);
    multi->addBox("join", "images/join.png", join);
    (*multi)["join"]->setTexture("images/join.png", "images/join.png");
    multi->addBackBox("images/back.png");

    menu_.addBox("single", "images/single.png", single);
    menu_.addBox("multi", "images/multi.png", multi);
    menu_.addBox("highscore", SelectBox::CHECKBOX);
    menu_.addBox("credits", SelectBox::CHECKBOX);
    menu_["highscore"]->setTexture("images/highscore.png", "images/highscore.png");
    menu_["credits"]->setTexture("images/credits.png", "images/credits.png");
    menu_.addBackBox("images/back.png");

    menu_.setStatus(SubObject::VISIBLE);
}

void	Menu::startSolo(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
}

void	Menu::joinServer(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "ip  : " << box->getInput("ip") << std::endl;
    std::cout << "port: " << box->getInput("port") << std::endl;
}

void	Menu::createServer(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
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
