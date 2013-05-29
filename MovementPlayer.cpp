/*
** MovementPlayer.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 13:31:28 2013 maxime ginters
** Last update Wed May 29 18:23:14 2013 vincent leroy
*/

#include <iostream>
#include <cmath>

#include "Log.h"
#include "ModelMgr.h"
#include "GameObject.h"
#include "MovementPlayer.h"

MovementPlayer::MovementPlayer(GameObject* obj) :
    AMovement(obj, MOVEMENTTYPE_PLAYER)
{}

void MovementPlayer::Initialize()
{}

void MovementPlayer::Update(uint32 const diff)
{
    if (_owner->GetMovementFlags() == 0)
        return ;

    float x = _owner->GetPositionX();
    float y = _owner->GetPositionY();
    float o = _owner->GetOrientation();
    float dist = _owner->GetSpeed() * diff / 1000.f;
    float angle = (_owner->HasMovementFlag(MOVEMENT_BACKWARD) ? M_PI : 0.f) + _owner->GetOrientation();
    float dx = x;
    float dy = y;

    if (_owner->HasMovementFlag(MOVEMENT_MOVING))
    {
        Mod2PI(angle);
        dx = x + dist * cosf(angle);
        dy = y + dist * sinf(angle);

        CollisionManager(x, y, angle, dist, dx, dy);
    }

    if (_owner->HasMovementFlag(MOVEMENT_TURN_LEFT))
        o += _owner->GetSpeedOr() * diff / 1000.f;
    else if (_owner->HasMovementFlag(MOVEMENT_TURN_RIGHT))
        o -= _owner->GetSpeedOr() * diff / 1000.f;

    Mod2PI(o);
    _owner->UpdatePosition(dx, dy, o);

    _owner->HandlePositionChange();
}

void MovementPlayer::Finish()
{}

void MovementPlayer::Abort(MovementTypes newType)
{
    (void)newType;
}

void MovementPlayer::CollisionManager(float x, float y, float angle, float dist, float &dx, float &dy) const
{
    std::list<const GameObject*> list;
    _owner->GetVisibleObject(list);

    std::list<const GameObject*>::const_iterator it;
    for (it = list.begin(); it != list.end(); ++it)
    {
        if (*it == _owner || (*it)->GetModelId() == 0 || AlreadyInWall(*it))
            continue;

        try
        {
            ModelBox box = sModelMgr->GetModelBoxAtPos(*it);
            ModelBox self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());
            if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                (self.max.y > box.min.y && self.min.y < box.max.y))
            {
                for (uint32 i = 0; i < 4; ++i)
                    if (angle >= i * M_PI_2 && angle <= (i + 1) * M_PI_2)
                    {
                        angle = i * M_PI_2;
                        break;
                    }

                dx = x + dist * cosf(angle);
                dy = y + dist * sinf(angle);

                self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());
                if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                    (self.max.y > box.min.y && self.min.y < box.max.y))
                {
                    for (uint32 i = 0; i < 4; ++i)
                        if (FuzzyCompare(angle, i * M_PI_2))
                        {
                            angle = (i + 1) * M_PI_2;
                            break;
                        }

                    dx = x + dist * cosf(angle);
                    dy = y + dist * sinf(angle);

                    self = sModelMgr->GetModelBoxAtPos(dx, dy, _owner->GetPositionZ(), _owner->GetModelId());
                    if ((self.max.x > box.min.x && self.min.x < box.max.x) &&
                        (self.max.y > box.min.y && self.min.y < box.max.y))
                    {
                        dx = x;
                        dy = y;
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            sLog->error("MovementPlayer : %s\n", e.what());
        }
    }
}

bool MovementPlayer::AlreadyInWall(const GameObject *obj) const
{
    try
    {
        ModelBox self = sModelMgr->GetModelBoxAtPos(_owner);
        ModelBox box = sModelMgr->GetModelBoxAtPos(obj);
        Model const* model = sModelMgr->GetModel(obj->GetModelId());
        if (!model)
            return false;

        float weight = model->width / 10;
        if ((self.max.x > (box.min.x + weight) && self.min.x < (box.max.x - weight)) &&
            (self.max.y > (box.min.y + weight) && self.min.y < (box.max.y - weight)))
            return true;
    }
    catch (const std::exception &e)
    {
        sLog->error("MovementPlayer : %s\n", e.what());
    }

    return false;
}
