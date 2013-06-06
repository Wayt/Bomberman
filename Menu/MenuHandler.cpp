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
        Server serv;
        if (serv.Initialize("0.0.0.0", "9000", 2) == false)
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
        Server serv;
        if (serv.Initialize("0.0.0.0", "9000", 2) == false)
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
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
}

