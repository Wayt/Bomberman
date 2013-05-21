/*
** Object.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue May 21 17:55:11 2013 maxime ginters
** Last update Tue May 21 18:38:54 2013 maxime ginters
*/

#ifndef OBJECT_H_
# define OBJECT_H_

#include "MapObject.h"
#include "ObjectAI.h"

class Object : public MapObject
{
public:
    Object(uint64 guid, uint32 modelId, std::string const& name);

    ObjectAI* GetAI();

    bool InitializeAI(std::string const& filename);
    bool ReloadAI();

    virtual void Update(uint32 const diff);

    static void RegisterLua(lua_State* state);
private:
    ObjectAI* _AI;
};

#endif /* !OBJECT_H_ */
