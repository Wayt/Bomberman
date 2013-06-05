/*
** ObjectAI.cpp for AI in /home/fest/Epitech/Bomberman/Server/AI
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:36:49 2013 maxime ginters
** Last update Wed Jun 05 20:35:48 2013 maxime ginters
*/

#include "ObjectAI.h"
#include "Object.h"
#include "MapObject.h"
#include "Map.h"

ObjectAI::ObjectAI(Object* obj, std::string const& file) : _me(obj),
    _file(file), _luastate(NULL)
{}

ObjectAI::~ObjectAI()
{}

bool ObjectAI::Initialize()
{
    _luastate = luaL_newstate();
    if (!_luastate)
        return false;

    try
    {
        luabind::open(_luastate);
        Object::RegisterLua(_luastate);
        MapObject::RegisterLua(_luastate);
        GameObject::RegisterLua(_luastate);
        Map::RegisterLua(_luastate);
        luabind::module(_luastate) [
            luabind::class_<Log>("Log")
            .def("print", &Log::print)
            ];
        luabind::globals(_luastate)["Log"] = sLog;
    }
    catch (std::exception const& e)
    {
        sLog->error("Error : %s", e.what());
        return false;
    }

    return ReloadLua();
}

bool ObjectAI::ReloadLua()
{
    if (!_luastate)
    {
        sLog->error("Error : can't reload lua, no luastate");
        return false;
    }
    if (luaL_dofile(_luastate, _file.c_str()) != 0)
    {
        sLog->error("Error : fail to do lua file");
        return false;
    }

    try
    {
        if (luabind::object f = luabind::globals(_luastate)["LoadScript"])
            f(_me);
    }
    catch (std::exception const&)
    {
        std::cerr << "ObjectAI::ReloadLua" << std::endl;
        LUA_RUNTIME_ERROR(_luastate);
    }

    return true;
}

void ObjectAI::UpdateAI(uint32 const diff)
{
    if (!_luastate)
        return;

    try
    {
        if (luabind::object f = luabind::globals(_luastate)["UpdateAI"])
            f(_me, diff);
    }
    catch (std::exception const&)
    {
        std::cerr << "ObjectAI::UpdateAI" << std::endl;
        LUA_RUNTIME_ERROR(_luastate);
    }
}

void ObjectAI::HandleHit(MapObject* obj)
{
    if (!_luastate)
        return;

    try
    {
        if (luabind::object f = luabind::globals(_luastate)["HandleHit"])
            f(_me, obj);
    }
    catch (std::exception const& e)
    {
        std::cerr << "ObjectAI::HandleHit - " << e.what() << std::endl;
        LUA_RUNTIME_ERROR(_luastate);
    }

}

void ObjectAI::HandleCross(GameObject* by)
{
    if (!_luastate)
        return;

    try
    {
        if (luabind::object f = luabind::globals(_luastate)["HandleCross"])
            f(_me, by);
    }
    catch (std::exception const& e)
    {
        std::cerr << "ObjectAI::HandleCross - " << e.what() << std::endl;
        LUA_RUNTIME_ERROR(_luastate);
    }
}
