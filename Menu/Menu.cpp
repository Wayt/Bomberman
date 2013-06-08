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
    InputBox *ib;

    /*{ single */
    SubMenu *single = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    /*{ single/load */
    SubMenu *load = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    load->addBox("map", SelectBox::INPUTBOX);
    (*load )["map"]->setTexture("Menu/images/map_file.png");

    load->addBox("start", SelectBox::CHECKBOX);
    (*load)["start"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");

    load->addBackBox("Menu/images/back.png");

    if ((ib = dynamic_cast<InputBox *>((*load)["map"])) != NULL)
	ib->addInput("map", 455, 283, 25, gdl::Color(39, 39, 39, 255));
    /*}*/

    single->addBox("config", SelectBox::INPUTBOX);
    (*single)["config"]->setTexture("Menu/images/single_config.png");
    if ((ib = dynamic_cast<InputBox *>((*single)["config"])) != NULL){
	ib->addInput("name", 455, 200, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("x", 455, 227, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("y", 455, 254, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("time", 455, 281, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("bot", 455, 308, 25, gdl::Color(39, 39, 39, 255));
    }

    single->addBox("new", SelectBox::CHECKBOX);
    (*single)["new"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");

    single->addBox("load", "Menu/images/load_game.png", load);
    single->addBackBox("Menu/images/back.png");
    /*}*/

    /*{ multi */
    SubMenu *multi = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    /*{ multi/create */
    SubMenu *create = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    create->addBox("config", SelectBox::INPUTBOX);
    (*create)["config"]->setTexture("Menu/images/single_config.png");
    if ((ib = dynamic_cast<InputBox *>((*create)["config"])) != NULL){
	ib->addInput("name", 455, 200, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("x", 455, 227, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("y", 455, 254, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("time", 455, 281, 25, gdl::Color(39, 39, 39, 255));
	ib->addInput("bot", 455, 308, 25, gdl::Color(39, 39, 39, 255));
    }
    create->addBox("start", SelectBox::CHECKBOX);
    (*create)["start"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");
    create->addBackBox("Menu/images/back.png");
    /*}*/
    /*{ multi/join */
    SubMenu *join = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);

    join->addBox("config", SelectBox::INPUTBOX);
    (*join)["config"]->setTexture("Menu/images/join_config.png");
    if ((ib = dynamic_cast<InputBox *>((*join)["config"])) != NULL){
	ib->addInput("name", 445, 260, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("ip", 445, 287, 25, gdl::Color(0, 255, 0, 255));
	ib->addInput("port", 445, 314, 25, gdl::Color(0, 255, 0, 255));
    }
    join->addBox("start", SelectBox::CHECKBOX);
    (*join)["start"]->setTexture("Menu/images/start_game.png", "Menu/images/start_game.png");
    join->addBackBox("Menu/images/back.png");
    /*}*/
    multi->addBox("create", "Menu/images/create_server.png", create);
    multi->addBox("join", "Menu/images/join_server.png", join);
    multi->addBackBox("Menu/images/back.png");
/*}*/

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
    InputBox *map;

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
    if ((*(*menu_["single"])["load"])["start"]->value() == 1){
	if (((map = dynamic_cast<InputBox*>((*(*menu_["single"])["load"])["map"])) != NULL) &&
		((box = dynamic_cast<InputBox*>((*menu_["single"])["config"])) != NULL))
	    startWithMap(box, map);
	(*(*menu_["single"])["load"])["start"]->select();
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
