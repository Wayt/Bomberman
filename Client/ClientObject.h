/*
** ClientObject.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:34 2013 maxime ginters
** Last update Wed May 15 18:26:13 2013 fabien casters
*/

#ifndef CLIENTOBJECT_H_
# define CLIENTOBJECT_H_

#include "Model.h"
#include "Position.h"

class ClientObject : public Position
{
public:
    ClientObject(uint64 guid, uint32 modelid, std::string const& name);

    uint64 GetGUID() const;
    Model &GetModel();

    void SetMovementFlags(uint32 flags);
private:
    uint64 _guid;
    uint32 _modelId;
    std::string _name;
    uint32 _movementFlags;
    Model _model;
};

#endif /* !CLIENTOBJECT_H_ */
