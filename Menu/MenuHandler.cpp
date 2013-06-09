//
// MenuHandler.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Thu Jun 06 22:26:06 2013 
// Last update Thu Jun 06 22:26:06 2013 
//

#include "MenuMonitor.h"
#include "Shared.h"
#include "Server.h"
#include "Client.h"
#include <unistd.h>

void	MenuMonitor::startSolo(InputBox *box, KeysMap kmap)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
    std::cout << "time: " << box->getInput("time") << std::endl;
    if ((box->getInput("name")).size() == 0 ||
	    (to<unsigned int>(box->getInput("mapx"))) < MAP_MIN_X ||
	    (to<unsigned int>(box->getInput("mapy"))) < MAP_MIN_Y ||
	    (to<unsigned int>(box->getInput("time"))) == 0 ){
	std::cout << "parametres invalides" << std::endl;
	return;
    }
    try 
    {
	Server serv;
	if (serv.Initialize("127.0.0.1", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000), to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), box->getInput("map")) == false)
	{
	    std::cout << "Fail to init serv" << std::endl;
	    ::exit(-1);
	}

	Client cli(kmap);
	if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
	{
	    std::cout << "Fail to init cli" << std::endl;
	    ::exit(-1);
	}
	serv.Start();
	cli.Join();
	serv.Join();
	serv.Stop();
	cli.Stop();
	initialize();
    }
    catch (const std::exception&)
    {
	::exit(-1);
    }
}

void	MenuMonitor::joinServer(InputBox *box, KeysMap kmap)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "ip  : " << box->getInput("ip") << std::endl;
    std::cout << "port: " << box->getInput("port") << std::endl;
    if ((box->getInput("name")).size() == 0 ||
	    (box->getInput("ip")).size() == 0 ||
	    (to<unsigned int>(box->getInput("port"))) == 0 ){
	std::cout << "parametres invalides" << std::endl;
	return;
    }
    try
    {
	Client cli(kmap);
	if (!cli.Start(box->getInput("ip"), box->getInput("port"), box->getInput("name")))
	{
	    std::cout << "Fail to init cli" << std::endl;
	    ::exit(-1);
	}
	cli.Join();
	cli.Stop();
	initialize();
    }
    catch (const std::exception&)
    {
	::exit(-1);
    }
}

void	MenuMonitor::createServer(InputBox *box, KeysMap kmap)
{
    std::cout << "name: " << box->getInput("name") << std::endl;
    std::cout << "mapx: " << box->getInput("x") << std::endl;
    std::cout << "mapy: " << box->getInput("y") << std::endl;
    std::cout << "bot: " << box->getInput("bot") << std::endl;
    std::cout << "time: " << box->getInput("time") << std::endl;
    if ((box->getInput("name")).size() == 0 ||
	    (to<unsigned int>(box->getInput("mapx"))) < MAP_MIN_X ||
	    (to<unsigned int>(box->getInput("mapy"))) < MAP_MIN_Y ||
	    (to<unsigned int>(box->getInput("time"))) == 0 ){
	std::cout << "parametres invalides" << std::endl;
	return;
    }
    try
    {
	Server serv;
	if (serv.Initialize("0.0.0.0", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000),
		    to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), box->getInput("map")) == false)
	{
	    std::cout << "Fail to init serv" << std::endl;
	    ::exit(-1);
	}

	Client cli(kmap);
	if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
	{
	    std::cout << "Fail to init cli" << std::endl;
	    ::exit(-1);
	}
	serv.Start();
	cli.Join();
	serv.Join();
	serv.Stop();
	cli.Stop();
	initialize();
    }
    catch (const std::exception&)
    {
	::exit(-1);
    }
}

void	MenuMonitor::startWithMap(InputBox *box, InputBox *map, KeysMap kmap)
{
    std::cout << "map: " << map->getInput("map") << std::endl;
    std::cout << "name: " << box->getInput("name") << std::endl;
    if ((box->getInput("name")).size() == 0 ||
	    (box->getInput("map")).size() == 0){
	std::cout << "parametres invalides" << std::endl;
	return;
    }
    try
    {
	Server serv;
	if (serv.Initialize("0.0.0.0", "9000", 2, to<unsigned int>(box->getInput("bot")), (to<unsigned int>(box->getInput("time")) * 1000), to<unsigned int>(box->getInput("x")), to<unsigned int>(box->getInput("y")), map->getInput("map")) == false)
	{
	    std::cout << "Fail to init serv" << std::endl;
	}

	Client cli(kmap);
	if (!cli.Start("127.0.0.1", "9000", box->getInput("name")))
	{
	    std::cout << "Fail to init cli" << std::endl;
	}
	serv.Start();
	cli.Join();
	serv.Join();
	serv.Stop();
	cli.Stop();
	initialize();
    }
    catch (const std::exception&)
    {
	::exit(-1);
    }
}
