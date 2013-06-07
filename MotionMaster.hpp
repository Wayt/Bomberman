/*
** MotionMaster.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 12:56:42 2013 maxime ginters
** Last update Fri Jun 07 15:16:28 2013 maxime ginters
*/

#ifndef MOTIONMASTER_H_
# define MOTIONMASTER_H_

#include <map>
#include "PathFindingRunnable.h"
#include "Shared.h"

class Map;
class GameObject;

enum MovementTypes
{
    MOVEMENTTYPE_NONE       = 0,
    MOVEMENTTYPE_IDLE       = 1,
    MOVEMENTTYPE_PLAYER     = 2,
    MOVEMENTTYPE_POINT      = 3
};

class AMovement
{
public:
    AMovement(GameObject* obj, MovementTypes type);
    virtual ~AMovement();

    virtual void Initialize() = 0;
    virtual void Update(uint32 const diff) = 0;
    virtual void Finish() = 0;
    virtual void Abort(MovementTypes newType) = 0;
    virtual void MovePoint(const point&, const Map*);
    virtual void MovePoint(const std::list<point> &);
    MovementTypes GetType() const;
    virtual void GetPathList(std::list<point>& list) const;

protected:
    GameObject* _owner;
    MovementTypes _type;
};

class MotionMaster
{
public:
    MotionMaster(GameObject* obj);
    virtual ~MotionMaster();

    void Initialize(MovementTypes moveType);

    MovementTypes GetMovementType() const;

    void Update(uint32 const diff);
    void MovePoint(const point &p, const Map* map);
    void MovePoint(const std::list<point> &points);
    void GetPathList(std::list<point>& list) const;
    void MoveIdle();

private:
    template<class T>
    AMovement* create() const
    {
        return new T(_owner);
    }

    GameObject* _owner;
    std::map<MovementTypes, AMovement* (MotionMaster::*)() const> _amovementMap;
    AMovement* _moveGen;
};


#endif /* !MOTIONMASTER_H_ */
