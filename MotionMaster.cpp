/*
** MotionMaster.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:51 2013 maxime ginters
** Last update Fri May 24 19:00:01 2013 maxime ginters
*/

#include "MotionMaster.hpp"
#include "Position.h"
#include "MovementIdle.h"
#include "MovementPlayer.h"

AMovement::AMovement(Position* obj, MovementTypes type) :
    _owner(obj), _type(type)
{}

AMovement::~AMovement()
{}

void AMovement::MovePoint(const point&)
{}

void AMovement::MovePoint(const std::list<point>&)
{}

MovementTypes AMovement::GetType() const
{
    return _type;
}

MotionMaster::MotionMaster(Position* obj) :
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

void MotionMaster::MovePoint(const point &p)
{
    Initialize(MOVEMENTTYPE_POINT);
    if (_moveGen)
        _moveGen->MovePoint(p);
}

void MotionMaster::MovePoint(const std::list<point> &points)
{
    Initialize(MOVEMENTTYPE_POINT);
    if (_moveGen)
        _moveGen->MovePoint(points);
}
