/*
** Main.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:21:22 2013 maxime ginters
** Last update Fri May 24 18:46:38 2013 fabien casters
*/

#include "Shared.h"
#include "Server.h"
#include "Client.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    Server serv;
    if (serv.Initialize("0.0.0.0", "9000", 2) == false)
    {
        std::cout << "Fail to init serv" << std::endl;
        return 1;
    }


    Client cli(KEYMAP_FR);
    if (!cli.Start("127.0.0.1", "9000", "Ta mere"))
    {
        std::cout << "Fail to init cli" << std::endl;
        return 1;
    }
    serv.Start();
    cli.Join();
    serv.Join();
    return 0;
}
