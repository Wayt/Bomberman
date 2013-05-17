/*
** ClientObject.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:34 2013 maxime ginters
** Last update Fri May 17 13:55:09 2013 maxime ginters
*/

#ifndef CLIENTOBJECT_H_
# define CLIENTOBJECT_H_

#include "Model.h"
#include "Position.h"
#include "MotionMaster.hpp"

class ClientObject : public Position
{
public:
    ClientObject(uint64 guid, uint32 modelid, std::string const& name);
    virtual ~ClientObject();

    uint64 GetGUID() const;
    Model &GetModel();

    void Update(uint32 const diff);

private:
    uint64 _guid;
    uint32 _modelId;
    std::string _name;
    Model _model;
    MotionMaster* _motionMaster;
};

#endif /* !CLIENTOBJECT_H_ */
