/*
** Session.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 15:47:46 2013 maxime ginters
** Last update Mon May 06 17:37:51 2013 maxime ginters
*/

#ifndef SESSION_H_
# define SESSION_H_

#include "Shared.h"
#include "SessionSocket.h"

class Session
{
public:
    Session(SessionSocket* sock);

    SessionSocket* GetSessionSocket();

private:
    SessionSocket* _socket;
};

#endif /* !SESSION_H_ */
