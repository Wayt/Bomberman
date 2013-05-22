/*
** ObjectAI.h for AI in /home/fest/Epitech/Bomberman/Server/AI
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:36:35 2013 maxime ginters
** Last update Wed May 22 13:35:42 2013 maxime ginters
*/

#ifndef OBJECTAI_H_
# define OBJECTAI_H_

extern "C"
{
  #include "lua5.1/lua.h"
  #include "lua5.1/lualib.h"
  #include "lua5.1/lauxlib.h"
}

#include "luabind/luabind.hpp"

#include <iostream>
#include <string>
#include "Shared.h"

#define LUA_RUNTIME_ERROR(a) sLog->error("LUA ERROR: %s", lua_tostring(a, -1))

class Object;

class ObjectAI
{
public:
    explicit ObjectAI(Object* obj, std::string const& file);
    virtual ~ObjectAI();

    bool Initialize();
    bool ReloadLua();

    void UpdateAI(uint32 const diff);

private:
    Object* _me;
    std::string _file;
    lua_State* _luastate;
};

#endif /* !OBJECTAI_H_ */
