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
#include "InputBox.h"

Menu::Menu(float x, float y, float z, float o) :
    AObject(x, y, z, o), menu_(_pos.x, _pos.y, _pos.z, _rot.x)
{


    SubMenu *single= new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    single->addBox("new", SelectBox::CHECKBOX);
    single->addBox("load", SelectBox::CHECKBOX);
    (*single)["new"]->setTexture("images/new.png", "images/new.png");
    (*single)["load"]->setTexture("images/load.png", "images/load.png");
    single->addBackBox("images/back.png");

    SubMenu *create = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    create->addBox("config", SelectBox::INPUTBOX);
    (*create)["config"]->setTexture("images/new.png");
    create->addBox("start", SelectBox::CHECKBOX);
    (*create)["start"]->setTexture("images/new_game.png", "images/new_game.png");
    create->addBackBox("images/back.png");

    SubMenu *join = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    join->addBox("config", SelectBox::INPUTBOX);
    (*join)["config"]->setTexture("images/new.png");
    join->addBox("start", SelectBox::CHECKBOX);
    (*join)["start"]->setTexture("images/new_game.png", "images/new_game.png");
    join->addBackBox("images/back.png");

    //SubMenu *join = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    SubMenu *multi = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    multi->addBox("create", "images/create.png", create);
    multi->addBox("join", "images/join.png", join);
    //multi->addBox("join", SelectBox::CHECKBOX);
    //(*multi)["create"]->setTexture("images/create.png", "images/create.png");
    (*multi)["join"]->setTexture("images/join.png", "images/join.png");
    multi->addBackBox("images/back.png");

    menu_.addBox("single", "images/single.png", single);
    menu_.addBox("multi", "images/multi.png", multi);
    menu_.addBox("highscore", SelectBox::CHECKBOX);
    menu_.addBox("credits", SelectBox::CHECKBOX);
    menu_["highscore"]->setTexture("images/highscore.png", "images/highscore.png");
    menu_["credits"]->setTexture("images/credits.png", "images/credits.png");


    //std::list<std::string> imglist;
    //imglist.push_back("images/new.png");
    //imglist.push_back("images/load.png");
    //imglist.push_back("images/create.png");
    //imglist.push_back("images/join.png");

    //menu_.addBox("test", imglist);
    //menu_.addBox("input", SelectBox::INPUTBOX);
    //menu_["input"]->setTexture("images/new.png");

    menu_.addBackBox("images/back.png");

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
	std::cout << "game started" << std::endl;
	(*menu_["single"])["new"]->select();
    }
    if ((*(*menu_["multi"])["create"])["start"]->value()  == 1){
	(*(*menu_["multi"])["create"])["start"]->select();
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["create"])["config"])) != NULL){
	    std::cout << "get conf" << std::endl;
	    std::cout << "name: " << box->getInput("name") << std::endl;
	    std::cout << "ip  : " << box->getInput("ip") << std::endl;
	    std::cout << "port: " << box->getInput("port") << std::endl;
	}
	std::cout << "server multi created" << std::endl;
    }
    if ((*(*menu_["multi"])["join"])["start"]->value()  == 1){
	(*(*menu_["multi"])["join"])["start"]->select();
	if ((box = dynamic_cast<InputBox*>((*(*menu_["multi"])["join"])["config"])) != NULL){
	    std::cout << "get conf:" << std::endl;
	    std::cout << "name: " << box->getInput("name") << std::endl;
	    std::cout << "ip  : " << box->getInput("ip") << std::endl;
	    std::cout << "port: " << box->getInput("port") << std::endl;
	}
	std::cout << "server multi join" << std::endl;
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
