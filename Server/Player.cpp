/*
** Player.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 14 14:49:16 2013 maxime ginters
** Last update Thu Jun 06 13:08:48 2013 maxime ginters
*/

#include "Player.h"
#include "Session.h"
#include "Map.h"

Player::Player(uint64 guid, std::string const& name, Session* sess) :
    MapObject(guid, MODELID_PLAYER, TYPEID_PLAYER, name),
    _session(sess), _telTimer(0)
{}

void Player::SetGrid(MapGrid* grid)
{
    MapGrid* oldGrid = _currGrid;
    MapObject::SetGrid(grid);

    if (_map && grid)
    {
        uint8 flags = _map->BuildGridUpdaterFlags(oldGrid, _currGrid);
        _map->GridUpdater(this, GRIDUPDATE_ACTIVE, flags);
    }
    if (oldGrid)
    {
        Packet data(SMSG_GRID_CHANGE_NOTIFY, 16);
        WritePosition(data);
        SendPacket(data);
    }
}

Session* Player::GetSession()
{
    return _session;
}

void Player::SendPacket(Packet const& data)
{
    _session->SendPacket(data);
}

void Player::HandleLogout()
{
    if (_map)
        _map->RemoveObject(this);
}

bool Player::HandleHit(MapObject* obj)
{
    if (!MapObject::HandleHit(obj))
        return false;

    SetAlive(false);
    SetKilledBy(obj->GetName());
    if (obj->GetOwner() > 0)
        SetKillerGUID(obj->GetOwner());
    else
        SetKillerGUID(obj->GetGUID());
    SetMovementFlags(0);
    SetRespawnTime(TIME_TO_RESPAWN);
    _telTimer = TIME_TO_RESPAWN / 3;

    _map->GridUpdater(this, GRIDUPDATE_KILLED, UPDATE_FULL);

    if (Score* sc = _map->GetScoreMgr().GetScore(GetGUID()))
    {
        sc->died += 1;
        _map->SendScores(GetGUID());
    }

    if (obj->GetOwner() != GetGUID())
        if (Score* sc = _map->GetScoreMgr().GetScore(obj->GetOwner()))
        {
            sc->killed += 1;
            _map->SendScores(obj->GetOwner());
        }
    return true;
}

void Player::Update(uint32 const diff)
{
    MapObject::Update(diff);

    if (_telTimer > 0)
    {
        if (_telTimer <= diff)
        {
            float x, y;
            _map->GetRandomStartPosition(x, y);
            _map->TeleportPlayer(this, x, y);
            _telTimer = 0;
        }
        else
            _telTimer -= diff;
    }
}

void Player::HandleRespawn()
{
    MapObject::HandleRespawn();

    _map->GridUpdater(this, GRIDUPDATE_RESPAWN, UPDATE_FULL);
}
