/*
** MotionMaster.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:51 2013 maxime ginters
** Last update Wed May 15 14:16:31 2013 maxime ginters
*/

#include "MotionMaster.hpp"
#include "MapObject.h"
#include "MovementIdle.h"
#include "MovementPlayer.h"

AMovement::AMovement(MapObject* obj, MovementTypes type) :
    _owner(obj), _type(type)
{}

AMovement::~AMovement()
{}

MovementTypes AMovement::GetType() const
{
    return _type;
}

MotionMaster::MotionMaster(MapObject* obj) :
    _owner(obj), _amovementMap(), _moveGen(NULL)
{
    _amovementMap.insert(
            std::make_pair<MovementTypes, AMovement* (MotionMaster::*)() const>(
            MOVEMENT_IDLE, &MotionMaster::create<MovementIdle>)
            );
    _amovementMap.insert(
            std::make_pair<MovementTypes, AMovement* (MotionMaster::*)() const>(
            MOVEMENT_PLAYER, &MotionMaster::create<MovementPlayer>)
            );
}

MotionMaster::~MotionMaster()
{
    if (_moveGen)
        _moveGen->Abort(MOVEMENT_NONE);
    delete _moveGen;
}

void MotionMaster::Initialize(MovementTypes moveType)
{
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
        return MOVEMENT_NONE;
    return _moveGen->GetType();
}

void MotionMaster::Update(uint32 const diff)
{
    if (!_moveGen)
        return;
    _moveGen->Update(diff);
}
