/*
** Main.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:21:22 2013 maxime ginters
** Last update Sat May 18 13:04:55 2013 maxime ginters
*/

#include "Shared.h"
#include "Server.h"
#include "Client.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;


    if (ac >= 3)
    {
        std::string kmap = "us";
        if (ac > 3)
            kmap = av[3];
        Client cli(kmap == "fr" ? KEYMAP_FR : KEYMAP_US);
        if (!cli.Start(av[1], av[2], "Wayt"))
        {
            std::cout << "Fail to init cli" << std::endl;
            return 1;
        }
        cli.Join();
    }
    else
    {
        Server serv;
        if (serv.Initialize("0.0.0.0", "9000", 2) == false)
        {
            std::cout << "Fail to init serv" << std::endl;
            return 1;
        }
        serv.Start();
        serv.Join();
    }
    return 0;
}
