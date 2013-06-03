/*
** Object.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:59:16 2013 maxime ginters
** Last update Mon Jun 03 19:02:28 2013 maxime ginters
*/

#include "Object.h"
#include "ObjectAI.h"

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
        ];
}

void Object::HandleHit(MapObject* obj)
{
    (void)obj;
    if (!IsInWorld())
        return;
    if (GetAI())
        GetAI()->HandleHit(obj);
    //std::cout << obj->GetName() << " HIT " << GetName() << std::endl;
    //_map->RemoveObject(this);

    if (GetModelId() == MODELID_WALL)
    {
        if (Score* sc = _map->GetScoreMgr().GetScore(obj->GetOwner()))
        {
            sc->wall += 1;
            _map->SendScores(obj->GetOwner());
        }
    }
}
