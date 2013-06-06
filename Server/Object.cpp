/*
** Object.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:59:16 2013 maxime ginters
** Last update Thu Jun 06 19:17:51 2013 maxime ginters
*/

#include "Object.h"
#include "ObjectAI.h"
#include "Speed.h"
#include "Range.h"
#include "More.h"
#include "Teleport.h"

Object::Object(uint64 guid, uint32 modelId, std::string const& name) : MapObject(guid, modelId, TYPEID_OBJECT, name),
    _AI(NULL)
{
}

Object::~Object()
{
    delete _AI;
}

ObjectAI* Object::GetAI()
{
    return _AI;
}

bool Object::InitializeAI(std::string const& filename)
{
    if (_AI)
    {
        sLog->error("Error : ai already loaded");
        return false;
    }

    _AI = new ObjectAI(this, filename);
    return _AI->Initialize();
}

bool Object::ReloadAI()
{
    if (!_AI)
    {
        sLog->error("Error : can't reload ai, there is no ai ...");
        return false;
    }
    return _AI->ReloadLua();
}

void Object::Update(uint32 const diff)
{
    MapObject::Update(diff);
    if (GetAI())
        GetAI()->UpdateAI(diff);
}

void Object::Despawn()
{
    if (GetMap())
        GetMap()->RemoveObject(this);
}

void Object::DoAction(uint32 id)
{
    (void)id;
}

void Object::RegisterLua(lua_State* state)
{
    luabind::module(state) [
        luabind::class_<Object>("Object")
        .def("GetName", &Object::GetName)
        .def("Despawn", &Object::Despawn)
        .def("DoAction", &Object::DoAction)
        .def("SpawnBonus", &Object::SpawnBonus)
        .def("CheckBonusCross", &Object::CheckBonusCross)
        .def("Kill", &Object::Kill)
        .def("MovePoint", &Object::MovePoint)
        .def("FindNearestPlayer", &Object::FindNearestPlayer)
        .def("IsPositionSafe", &Object::IsPositionSafe)
        ];
}

bool Object::HandleHit(MapObject* obj)
{
    (void)obj;
    if (!IsInWorld())
        return false;
    if (!MapObject::HandleHit(obj))
        return false;
    Map* savedMap = _map;
    if (GetAI())
        GetAI()->HandleHit(obj);

    if (GetModelId() == MODELID_WALL)
    {
        if (Score* sc = savedMap->GetScoreMgr().GetScore(obj->GetOwner()))
        {
            sc->wall += 1;
            savedMap->SendScores(obj->GetOwner());
        }
    }
    return true;
}

void Object::HandleCross(MapObject* by)
{
    if (GetAI())
        GetAI()->HandleCross(by);
}

void Object::SpawnBonus()
{
    if ((rand() % 5) != 0)
        return ;

    uint32 r = rand() % 4;
    Object *bonus = NULL;

    switch (r)
    {
        case 0:
            bonus = new Speed(GetMap()->MakeNewGuid());
            break;
        case 1:
            bonus = new Range(GetMap()->MakeNewGuid());
            break;
        case 2:
            bonus = new More(GetMap()->MakeNewGuid());
            break;
        case 3:
            bonus = new Teleport(GetMap()->MakeNewGuid());
        default:
            break;
    }

    if (!bonus)
        return ;

    bonus->UpdatePosition(GetPositionX(), GetPositionY(), GetPositionZ(), 0.f);
    GetMap()->AddObject(bonus);
}

void Object::CheckBonusCross(float range)
{
    std::list<MapObject*> list;
    GetObjectListInRange(range, list);

    for (std::list<MapObject*>::const_iterator itr = list.begin(); itr != list.end(); ++itr)
        if ((*itr)->GetTypeId() == TYPEID_PLAYER)
        {
            HandleCross(*itr);
            break;
        }
}

void Object::HandleRespawn()
{
    MapObject::HandleRespawn();

    if (GetAI())
        GetAI()->HandleRespawn();
}

void Object::MovePoint(float x, float y)
{
    point pt = std::pair<float, float>(x, y);
    GetMotionMaster()->MovePoint(pt);
}

void Object::HandlePathGenerated(std::list<point> const& path)
{
    Packet data(SMSG_SEND_PATH, 8 + 16 + 4 + (path.size() * 8));
    data << uint64(GetGUID());
    WritePosition(data);
    data << uint32(path.size());
    for (std::list<point>::const_iterator itr = path.begin(); itr != path.end(); ++itr)
    {
        data << float((*itr).first);
        data << float((*itr).second);
    }
    GetMap()->BroadcastToAll(data);

    if (GetAI())
        GetAI()->HandlePathGenerated();
}

void Object::HandleFailToCreatePath()
{
    if (GetAI())
        GetAI()->HandleFailToCreatePath();
}

void Object::HandleFinishMovePoint()
{
    if (GetAI())
        GetAI()->HandleFinishMovePoint();
}

MapObject* Object::FindNearestPlayer()
{
    std::list<MapObject*> list;
    GetObjectListInRange(100.0f, list);

    MapObject* obj = NULL;
    float dist = 200.0f * 200.0f;

    for (std::list<MapObject*>::const_iterator itr = list.begin(); itr != list.end(); ++itr)
        if ((*itr)->GetTypeId() == TYPEID_PLAYER)
        {
            if (!obj)
                obj = *itr;
            else
            {
                float d = GetDistance2dSquare(*itr);
                if (d < dist)
                {
                    dist = d;
                    obj = *itr;
                }
            }
        }
    return obj;
}

class WallPositionCheck
{
public:
    WallPositionCheck(float x, float y) :
        _posx(x), _posy(y)
    {}

    bool operator()(MapObject const* obj)
    {
        if (FuzzyCompare(_posx, obj->GetPositionX()) && FuzzyCompare(_posy, obj->GetPositionY()))
            return true;
        return false;
    }
private:
    float _posx;
    float _posy;
};

bool Object::CanBeHitBy(MapObject* bomb, std::list<MapObject*> const& list) const
{
    float bx, by, sx, sy;
    bomb->GetBoxCenter(bx, by);
    GetBoxCenter(sx, sy);

    if (!((bx >= (sx - 2.5f) && bx <= (sx + 2.5f)) ||
            (by >= (sy - 2.5f) && by <= (sy + 2.5f))))
        return false;

    if (bomb->GetDistance2dSquare(sx, sy) > (bomb->GetBombRange() * bomb->GetBombRange()))
        return false;

    if (FuzzyCompare(sx, bx)) // Translate on y
    {
        if (sy < by)
        {
            for (float y = sy + 5.0f; y < by; y += 5.0f)
                if (std::count_if(list.begin(), list.end(), WallPositionCheck(sx, y)) >= 1)
                    return false;
        }
        else
        {
            for (float y = sy - 5.0f; y > by; y -= 5.0f)
                if (std::count_if(list.begin(), list.end(), WallPositionCheck(sx, y)) >= 1)
                    return false;
        }

    }
    else if (FuzzyCompare(sy, by)) // Translate on x
    {
        if (sx < bx)
        {
            for (float x = sx + 5.0f; x < bx; x += 5.0f)
                if (std::count_if(list.begin(), list.end(), WallPositionCheck(x, sy)) >= 1)
                    return false;
        }
        else
        {
            for (float x = sx - 5.0f; x > bx; x -= 5.0f)
                if (std::count_if(list.begin(), list.end(), WallPositionCheck(x, sy)) >= 1)
                    return false;
        }

    }
    return true;
}

bool Object::IsPositionSafe() const
{
    std::list<MapObject*> list;
    float bx, by;

    GetBoxCenter(bx, by);
    GetMap()->GetObjectListInRange(bx, by, 100.0f, list);


    for (std::list<MapObject*>::const_iterator itr = list.begin(); itr != list.end(); ++itr)
        if (MapObject* obj = *itr)
            if (obj->GetModelId() == MODELID_BOMB)
            {
                if (CanBeHitBy(obj, list))
                    return false;
            }
    return true;
}
