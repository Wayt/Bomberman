/*
** MotionMaster.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:42 2013 maxime ginters
** Last update Wed May 15 14:10:08 2013 maxime ginters
*/

#ifndef MOTIONMASTER_H_
# define MOTIONMASTER_H_

#include <map>
#include "Shared.h"

class MapObject;

enum MovementTypes
{
    MOVEMENT_NONE       = 0,
    MOVEMENT_IDLE       = 1,
    MOVEMENT_PLAYER     = 2,
};

class AMovement
{
public:
    AMovement(MapObject* obj, MovementTypes type);
    virtual ~AMovement();

    virtual void Initialize() = 0;
    virtual void Update(uint32 const diff) = 0;
    virtual void Finish() = 0;
    virtual void Abort(MovementTypes newType) = 0;
    MovementTypes GetType() const;

protected:
    MapObject* _owner;
    MovementTypes _type;
};

class MotionMaster
{
public:
    MotionMaster(MapObject* obj);
    virtual ~MotionMaster();

    void Initialize(MovementTypes moveType);

    MovementTypes GetMovementType() const;

    void Update(uint32 const diff);
private:
    template<class T>
    AMovement* create() const
    {
        return new T(_owner);
    }

    MapObject* _owner;
    std::map<MovementTypes, AMovement* (MotionMaster::*)() const> _amovementMap;
    AMovement* _moveGen;
};


#endif /* !MOTIONMASTER_H_ */
