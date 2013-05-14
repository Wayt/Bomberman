/*
** Player.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 14:49:16 2013 maxime ginters
** Last update Tue May 14 17:13:29 2013 maxime ginters
*/

#include "Player.h"
#include "Session.h"
#include "Map.h"

Player::Player(uint64 guid, std::string const& name, Session* sess) :
    MapObject(guid, MODELID_PLAYER, TYPEID_PLAYER, name),
    _session(sess)
{}

void Player::SetGrid(MapGrid* grid)
{
    MapGrid* oldGrid = _currGrid;
    MapObject::SetGrid(grid);

    if (_map)
    {
        uint8 flags = _map->BuildGridUpdaterFlags(oldGrid, _currGrid);
        _map->GridUpdater(this, GRIDUPDATE_ACTIVE | GRIDUPDATE_SENDOBJ, flags);
    }
}

Session* Player::GetSession()
{
    return _session;
}