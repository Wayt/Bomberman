/*
** MotionMaster.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:51 2013 maxime ginters
** Last update Fri Jun 07 15:01:21 2013 maxime ginters
*/

#include <iostream>

#include "Map.h"
#include "MotionMaster.hpp"
#include "GameObject.h"
#include "MovementIdle.h"
#include "MovementPlayer.h"
#include "MovementPoint.h"

AMovement::AMovement(GameObject* obj, MovementTypes type) :
    _owner(obj), _type(type)
{}

AMovement::~AMovement()
{}

void AMovement::MovePoint(const point&, const Map*)
{}

void AMovement::MovePoint(const std::list<point>&)
{}

MovementTypes AMovement::GetType() const
{
    return _type;
}

void AMovement::GetPathList(std::list<point>& list) const
{
    (void)list;
}

MotionMaster::MotionMaster(GameObject* obj) :
    _owner(obj), _amovementMap(), _moveGen(NULL)
{
    _amovementMap.insert(
            std::make_pair<MovementTypes, AMovement* (MotionMaster::*)() const>(
            MOVEMENTTYPE_IDLE, &MotionMaster::create<MovementIdle>)
            );
    _amovementMap.insert(
            std::make_pair<MovementTypes, AMovement* (MotionMaster::*)() const>(
            MOVEMENTTYPE_PLAYER, &MotionMaster::create<MovementPlayer>)
            );
    _amovementMap.insert(
            std::make_pair<MovementTypes, AMovement* (MotionMaster::*)() const>(
            MOVEMENTTYPE_POINT, &MotionMaster::create<MovementPoint>)
            );
}

MotionMaster::~MotionMaster()
{
    if (_moveGen)
        _moveGen->Abort(MOVEMENTTYPE_NONE);
    delete _moveGen;
}

void MotionMaster::Initialize(MovementTypes moveType)
{
    if (_moveGen && _moveGen->GetType() == moveType)
    {
        _moveGen->Abort(moveType);
        return;
    }

    std::map<MovementTypes, AMovement* (MotionMaster::*)() const>::const_iterator itr;
    itr = _amovementMap.find(moveType);
    if (itr == _amovementMap.end())
    {
        sLog->error("Error : invalide move type : %u", moveType);
        return;
    }

    if (_moveGen)
        _moveGen->Abort(moveType);
    delete _moveGen;
    _moveGen = NULL;

    _moveGen = (this->*itr->second)();
    _moveGen->Initialize();
}

MovementTypes MotionMaster::GetMovementType() const
{
    if (!_moveGen)
        return MOVEMENTTYPE_NONE;
    return _moveGen->GetType();
}

void MotionMaster::Update(uint32 const diff)
{
    if (!_moveGen)
        return;
    _moveGen->Update(diff);
}

void MotionMaster::MovePoint(const point &p, const Map *map)
{
    Initialize(MOVEMENTTYPE_POINT);
    if (_moveGen)
        _moveGen->MovePoint(p, map);
}

void MotionMaster::MovePoint(const std::list<point> &points)
{
    Initialize(MOVEMENTTYPE_POINT);
    if (_moveGen)
        _moveGen->MovePoint(points);
}

void MotionMaster::GetPathList(std::list<point>& path) const
{
    if (!_moveGen)
        return;
    if (_moveGen->GetType() != MOVEMENTTYPE_POINT)
        return;
    _moveGen->GetPathList(path);
}
