/*
** Main.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Sat May 04 15:21:22 2013 maxime ginters
** Last update Mon May 06 17:53:56 2013 maxime ginters
*/

#include "Shared.h"
#include "Server.h"

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
    serv.Start();
    serv.Join();
    return 0;
}
