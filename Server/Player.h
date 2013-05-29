/*
** Player.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 14:44:16 2013 maxime ginters
** Last update Wed May 29 15:08:55 2013 maxime ginters
*/

#ifndef PLAYER_H_
# define PLAYER_H_

#include "MapObject.h"

class Session;

class Player : public MapObject
{
public:
    Player(uint64 guid, std::string const& name, Session* sess);

    void SetGrid(MapGrid* grid);

    Session* GetSession();

    void SendPacket(Packet const& data);

    void HandleLogout();

    void HandleHit(MapObject* obj);

private:
    Session* _session;
};

#endif /* !PLAYER_H_ */
