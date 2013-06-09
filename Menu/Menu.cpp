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
#include "Client.h"
#include "Image.hpp"
#include "CheckBox.h"
#include "Highscores.h"

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
    SubMenu *settings = new SubMenu(_pos.x, _pos.y, _pos.z, _rot.x);
    settings->addBox("keymap", SelectBox::CHECKBOX);
    (*settings)["keymap"]->setTexture("Menu/images/keyus.png", "Menu/images/keyfr.png");
    settings->addBackBox("Menu/images/back.png");

    SubMenu *credits = new SubMenu(_pos.x - 150, _pos.y, _pos.z, _rot.x);
    credits->addBackBox("Menu/images/credits_img.png");

    SubMenu *highscore = new SubMenu(_pos.x - 150, _pos.y, _pos.z, _rot.x);
    Highscores *h = new Highscores(_pos.x - 150, _pos.y, _pos.z, _rot.x);
    h->setRet(false);
    h->setTexture("Menu/images/highscores_img.png");
    highscore->addObject(h);

    menu_.addBox("single", "Menu/images/single.png", single);
    menu_.addBox("multi", "Menu/images/multi.png", multi);
    menu_.addBox("settings", "Menu/images/settings.png", settings);
    menu_.addBox("highscore", "Menu/images/highscore.png", highscore);
    menu_.addBox("credits", "Menu/images/credits.png", credits);
    menu_.addBackBox("Menu/images/quit.png");

    menu_.setStatus(SubObject::VISIBLE);
}

void Menu::initialize()
{
    menu_.initialize();
}

SubMenu &Menu::getMenu()
{
    return menu_;
}

void Menu::update(gdl::GameClock const &clock, gdl::Input &input)
{ 
    menu_.update(clock, input);
    usleep(1000);
}

void Menu::draw()
{
    menu_.draw();
}

Menu::~Menu()
{
}
