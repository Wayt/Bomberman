/*
** MotionMaster.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:42 2013 maxime ginters
** Last update Thu May 16 18:32:16 2013 maxime ginters
*/

#ifndef MOTIONMASTER_H_
# define MOTIONMASTER_H_

#include <map>
#include "Shared.h"

class MapObject;

enum MovementTypes
{
    MOVEMENTTYPE_NONE       = 0,
    MOVEMENTTYPE_IDLE       = 1,
    MOVEMENTTYPE_PLAYER     = 2,
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
