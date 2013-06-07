//
// MenuHandler.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Thu Jun 06 22:26:06 2013 
// Last update Thu Jun 06 22:26:06 2013 
//

#include "Menu.h"
#include "Shared.h"
#include "Server.h"
#include "Client.h"

void	Menu::startSolo(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
    std::cout << "time: " << box->getInput("time") << std::endl;
    Server serv;
    if (serv.Initialize("127.0.0.1", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000), to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), box->getInput("map")) == false)
    {
	std::cout << "Fail to init serv" << std::endl;
    }

    Client cli(KEYMAP_US);
    if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
    {
	std::cout << "Fail to init cli" << std::endl;
    }
    serv.Start();
    cli.Join();
    serv.Join();
}

void	Menu::joinServer(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "ip  : " << box->getInput("ip") << std::endl;
    std::cout << "port: " << box->getInput("port") << std::endl;
    Client cli(KEYMAP_US);
    if (!cli.Start(box->getInput("ip"), box->getInput("port"), box->getInput("name")))
    {
	std::cout << "Fail to init cli" << std::endl;
    }
    cli.Join();
}

void	Menu::createServer(InputBox *box)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
    std::cout << "time: " << box->getInput("time") << std::endl;
    Server serv;
    if (serv.Initialize("0.0.0.0", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000), to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), box->getInput("map")) == false)
    {
	std::cout << "Fail to init serv" << std::endl;
    }

    Client cli(KEYMAP_US);
    if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
    {
	std::cout << "Fail to init cli" << std::endl;
    }
    serv.Start();
    cli.Join();
    serv.Join();
}

void	Menu::startWithMap(InputBox *box, InputBox *map)
{
    std::cout << "map: " << map->getInput("map") << std::endl;
    std::cout << "name: " << box->getInput("name") << std::endl;

    Server serv;
    if (serv.Initialize("0.0.0.0", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000), to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), map->getInput("map")) == false)
    {
	std::cout << "Fail to init serv" << std::endl;
    }

    Client cli(KEYMAP_US);
    if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
    {
	std::cout << "Fail to init cli" << std::endl;
    }
    serv.Start();
    cli.Join();
    serv.Join();
}
