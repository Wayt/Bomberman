/*
** Object.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:59:16 2013 maxime ginters
** Last update Wed Jun 05 22:22:12 2013 vincent leroy
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
        ];
}

void Object::HandleHit(MapObject* obj)
{
    (void)obj;
    if (!IsInWorld())
        return;
    Map* savedMap = _map;
    if (GetAI())
        GetAI()->HandleHit(obj);
    //std::cout << obj->GetName() << " HIT " << GetName() << std::endl;
    //_map->RemoveObject(this);

    if (GetModelId() == MODELID_WALL)
    {
        if (Score* sc = savedMap->GetScoreMgr().GetScore(obj->GetOwner()))
        {
            sc->wall += 1;
            savedMap->SendScores(obj->GetOwner());
        }
    }
}

void Object::HandleCross(GameObject* by)
{
    if (GetAI())
        GetAI()->HandleCross(by);
}

void Object::SpawnBonus()
{
    if ((rand() % 10) != 0)
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
