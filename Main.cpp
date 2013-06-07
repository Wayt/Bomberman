/*
** Main.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:21:22 2013 maxime ginters
** Last update Fri Jun 07 17:46:53 2013 maxime ginters
*/

#include "Shared.h"
#include "Server.h"
#include "Client.h"
#include "MenuMonitor.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    if (ac >= 2)
    {
        if (std::string(av[1]) == "-debug")
        {
            Server serv;
            if (serv.Initialize("0.0.0.0", "9000", 2, 5, 60000, 10, 10, "") == false)
            {
                std::cout << "Fail to init serv" << std::endl;
                return 1;
            }

            Client cli(KEYMAP_US);
            if (!cli.Start("127.0.0.1", "9000", "Host"))
            {
                std::cout << "Fail to init cli" << std::endl;
                return 1;
            }
            serv.Start();
            cli.Join();
            serv.Join();
            return 0;
        }

    }
    MenuMonitor menu(NULL, 50, 50);
    menu.run();
    return 0;
}

//int main(int ac, char **av)
//{
    //(void)ac;
    //(void)av;

    //if (ac < 4)
    //{
        //Server serv;
        //if (serv.Initialize("0.0.0.0", "9000", 2) == false)
        //{
            //std::cout << "Fail to init serv" << std::endl;
            //return 1;
        //}

        //std::string kmap = "us";
        //if (ac >= 2)
            //kmap = av[1];
        //Client cli(kmap == "fr" ? KEYMAP_FR : KEYMAP_US);
        //if (!cli.Start("127.0.0.1", "9000", "Host"))
        //{
            //std::cout << "Fail to init cli" << std::endl;
            //return 1;
        //}
        //serv.Start();
        //cli.Join();
        //serv.Join();
    //}
    //else
    //{
        //std::string kmap = "us";
        //if (ac >= 5)
            //kmap = av[4];
        //Client cli(kmap == "fr" ? KEYMAP_FR : KEYMAP_US);
        //if (!cli.Start(av[1], av[2], av[3]))
        //{
            //std::cout << "Fail to init cli" << std::endl;
            //return 1;
        //}
        //cli.Join();
    //}
    //return 0;
//}
